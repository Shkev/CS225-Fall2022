/**
 * @file schedule.h
 * Exam scheduling using graph coloring
 */

#pragma once

#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <set>
#include <algorithm>

typedef std::vector<std::vector<std::string>> V2D;
typedef int Color;

using std::unordered_map;
using std::unordered_set;
using std::string;
using std::list;
using std::vector;


class Graph {
public:
  Graph() = default;
  Graph(V2D course_rosters);

  unordered_set<string> GetNodes();
  unsigned GetNodeDegree(string node);

  /**
   * Implements green heuristic introduced in MP instructions
   * @param coloring The map that will store the color corresponding to each course in the coloring
   * @returns true if a coloring is possible and false if not.
  */
  bool ColorIt(unsigned max_colors, unordered_map<string, Color>& coloring);

private:
  /**
   * Graph stores nodes representing courses. There exists an edge
   * between courses if there exists student(s) that is both classes
 */
  unordered_map<string, unordered_set<string>> adj_list_;
  vector<std::pair<string, unsigned>> node_degree_;
  unordered_set<string> nodes_;
};


/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. You must preserve the order from the input file.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 * @return The vector of vectors of strings imported from filename
 */
V2D file_to_V2D(const std::string & filename);

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param course A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 * @return A 2D vector of strings where each row is a course followed by all the students in the course
 */
V2D clean(const V2D & cv, const V2D & sv);

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * If a valid solution cannot be formed after <XXX: How many iterations?> iterations of graph coloring, return a V2D with one row
 * with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 * @return A 2D vector which each row is a timeslot with all the courses scheduled for that time
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots);
