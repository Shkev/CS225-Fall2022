/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cassert>

#include "schedule.h"
#include "utils.h"

using std::string;
using std::vector;
using std::list;
using std::unordered_map;
using std::unordered_set;

Graph::Graph(V2D course_rosters) {
    // keep track of what students are in each course. Makes it easier to create edges in graph
    unordered_map<string, unordered_set<string>> course_students;
    for (auto course_it = course_rosters.begin(); course_it != course_rosters.end(); ++course_it) {
        const vector<string>& course_entry = *course_it;
        string course_name = course_entry.at(0);
        course_students.insert({course_name, unordered_set<string>(course_entry.begin()+1, course_entry.end())});
        
        unordered_set<string> adj_courses;
        // for every student in this class check if they are in the previous classes
        for (auto stu_it = course_entry.begin()+1; stu_it != course_entry.end(); ++stu_it) {
            for (auto prev_it = course_rosters.begin(); prev_it != course_it; ++prev_it) {
                string prev_course_name = prev_it->at(0);
                if (course_students.at(prev_course_name).count(*stu_it) > 0) {
                    adj_courses.insert(prev_course_name);
                    adj_list_.at(prev_course_name).insert(course_name);
                }
            }
        }
        adj_list_.insert({course_name, adj_courses});
        nodes_.insert(course_name);
    }
    for (string node : nodes_) {
        node_degree_.push_back({node, GetNodeDegree(node)});
    }
    // sort greatest to least by degree
    std::sort(node_degree_.begin(), node_degree_.end(), [](auto a, auto b){
        return a.second > b.second;
    });
}

unordered_set<string> Graph::GetNodes() {
    return nodes_;
}

bool Graph::ColorIt(unsigned max_colors, unordered_map<string, Color>& coloring) {
    coloring.clear();
    for (string node : nodes_) {
        coloring.insert({node, -1}); // -1 means it hasn't been colored yet
    }
    coloring.at(node_degree_.at(0).first) = 0;
    for (auto p : node_degree_) {
        vector<bool> used_colors(max_colors, false);
        string curr_node = p.first;
        if (coloring.at(curr_node) != -1) continue; // already colored
        for (string neighbor : adj_list_.at(curr_node)) {
            if (coloring.at(neighbor) == -1) continue;
            used_colors.at(coloring.at(neighbor)) = true;
        }
        size_t c;
        for (c = 0; c < used_colors.size(); ++c) {
            if (used_colors.at(c) == false) break;
        }
        if (c >= max_colors) return false;
        coloring.at(curr_node) = c;
    }
    return true;
}

unsigned Graph::GetNodeDegree(string node) {
    if (adj_list_.count(node) == 0) {
        throw std::out_of_range("Node '" + node + "' does not exist!");
    }
    return adj_list_.at(node).size();
}

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const string & filename){
    // Your code here!
    V2D data;
    string csv_contents = file_to_string(filename);
    vector<string> csv_entries;
    SplitString(csv_contents, '\n', csv_entries);
    for (const string& data_entry : csv_entries) {
        vector<string> features;
        SplitString(data_entry, ',', features);
        for (string& feat : features) { // remove whitespace
            feat = Trim(feat);
        }
        data.push_back(features);
    }
    return data;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    unordered_map<string, unordered_set<string>> student_courses;
    for (const vector<string>& student_entry : student) {
        assert(student_entry.size() >= 1); // each entry contains at least student name
        string student_name = student_entry.at(0);
        student_courses.insert({student_name, unordered_set<string>(student_entry.begin()+1, student_entry.end())});
    }

    V2D cleaned_course_roster;
    for (const vector<string>& course_entry : cv) {
        assert(course_entry.size() >= 1);
        string course_name = course_entry.at(0);
        vector<string> cleaned_course_entry = {course_name};
        std::copy_if(course_entry.begin()+1, course_entry.end(), std::back_inserter(cleaned_course_entry),\
                    [&](const string& stu) {
                        if (student_courses.count(stu) == 0) return false; // if student doesn't exist
                        unordered_set<string> stu_planned_courses = student_courses.at(stu);
                        // return true if the student know they are enrolled in this class
                        return stu_planned_courses.count(course_name) > 0;
                    });
        if (cleaned_course_entry.size() > 1) { // if course has valid students after cleaning add it to data
            cleaned_course_roster.push_back(cleaned_course_entry);
        }
    }
    return cleaned_course_roster;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const vector<string> &timeslots){
    // Your code here!
    Graph course_graph(courses);
    unordered_map<string, Color> graph_coloring;
    bool colorable = course_graph.ColorIt(timeslots.size(), graph_coloring);
    if (!colorable) {
        return {{"-1"}};
    }
    V2D schedule(timeslots.size(), vector<string>());
    for (size_t i = 0; i < timeslots.size(); ++i) {
        schedule.at(i).push_back(timeslots.at(i));
    }
    for (std::pair<string, Color> course : graph_coloring) {
        assert(course.second >= 0);
        schedule.at(course.second).push_back(course.first);
    }
    return schedule;
}
