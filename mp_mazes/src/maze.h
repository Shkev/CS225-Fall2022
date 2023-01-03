/* Your code here! */
#pragma once

#include <algorithm>
#include <vector>
#include <queue>
#include <random>
#include <iostream>
#include <cassert>
#include "dsets.h"
#include "cs225/PNG.h"

using std::vector;
using std::queue;
using std::pair;
using namespace cs225;

class SquareMaze {
private:
    struct Square {
        bool left = true;
        bool right = true;
        bool top = true;
        bool bottom = true;

        bool& GetWall(int dir);

        bool operator==(const Square& other);
    };

    struct Point {
        int x = -1;
        int y = -1;

        Point(): x(-1), y(-1) {}
        Point(int xs, int ys): x(xs), y(ys) {}

        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
        friend std::ostream& operator<<(std::ostream& os, const Point& p);
    };

    struct Location {
        Point coord;
        int dist_from_origin = 0;
        bool visited = false;
        Point pred;

        Location(): coord(Point()), dist_from_origin(0), visited(false), pred(Point()) {}

        Location(int xs, int ys) {
            coord = Point(xs, ys);
        }

        friend std::ostream& operator<<(std::ostream& os, const Location& loc);

        bool HasPredecessor();
        vector<Point> GetAdjPts(const vector<vector<Location>>& maze_locs) const;
        int DetermineDirectionTo(const Point& pt) const;
        int DetermineDirectionTo(const Location& loc) const;
    };

public:
    SquareMaze() = default;

    void makeMaze(int width, int height);

    bool canTravel(int x, int y, int dir);

    void setWall(int x, int y, int dir, bool exists);

    vector<int> solveMaze();

    PNG* drawMaze() const;

    PNG* drawMazeWithSolution();

private:
    vector<vector<Square>> maze_;
    static const HSLAPixel kBlackPixel_;
    static const HSLAPixel kWhitePixel_;
    static const HSLAPixel kRedPixel_;
    static std::mt19937 urng_;

    int GetWidth() const;
    int GetHeight() const;
    void Clear();

    vector<int> TraceMazeSolnPath(const vector<vector<Location>>& maze_locs, const Location& maze_end) const;

    vector<Point> FilterValidPts(vector<Point> points, const Location& curr_loc);
    bool IsInMazeBounds(const Point& p) const;
    /**
     * Converts index of array representation of 2D grid to Point(x, y)
     * where that item should be in the grid.
    */
    Point ArrToGridIdx(int arr_idx, int height, int width) const;

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::ostream& operator<<(std::ostream& os, const Location& loc);
};