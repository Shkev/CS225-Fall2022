/* Your code here! */
#include "maze.h"

std::random_device rng;
std::mt19937 SquareMaze::urng_ = std::mt19937(rng());
const HSLAPixel SquareMaze::kBlackPixel_ = HSLAPixel(0, 0, 0);
const HSLAPixel SquareMaze::kWhitePixel_ = HSLAPixel(1, 1, 1);
const HSLAPixel SquareMaze::kRedPixel_ = HSLAPixel(0, 1, 0.5);

vector<int> SquareMaze::solveMaze() {
    // finding maze path using BFS
    vector<vector<Location>> maze_locs(GetHeight(), vector<Location>(GetWidth()));
    queue<Location> q;
    Location& start_maze = maze_locs.at(0).at(0); // origin (top left corner)
    start_maze.visited = true;
    start_maze.coord = Point(0, 0);
    q.push(start_maze);
    Location end_maze;
    while (!q.empty()) {
        const Location& kCurrLoc = q.front();
        q.pop();
        // std::cout << kCurrLoc << "\n\n";
        if (kCurrLoc.coord.y == GetHeight()-1 && kCurrLoc.dist_from_origin > end_maze.dist_from_origin) {
            end_maze = kCurrLoc;
        }
        for (const Point& adj_pt : FilterValidPts(kCurrLoc.GetAdjPts(maze_locs), kCurrLoc)) {
            Location& adj_loc = maze_locs.at(adj_pt.y).at(adj_pt.x);
            adj_loc.coord = adj_pt;
            if (!adj_loc.visited) {
                adj_loc.visited = true;
                adj_loc.pred = kCurrLoc.coord; // set predecessor of the adj_loc to curr_loc
                adj_loc.dist_from_origin = kCurrLoc.dist_from_origin + 1;
                q.push(adj_loc);
            }
        }
    }
    // std::cout << end_maze << "\n";
    return TraceMazeSolnPath(maze_locs, end_maze);
}

void SquareMaze::makeMaze(int width, int height) {
    Clear();
    maze_.resize(height, vector<Square>(width));
    assert(maze_.at(0).at(0) == Square());

    // use disjoint sets to keep track of maze path and prevent cycles
    DisjointSets ds;
    int maze_size = width*height;
    ds.addelements(maze_size); // representing maze as 1D array
    
    vector<int> maze_indices(maze_size);
    std::iota(maze_indices.begin(), maze_indices.end(), 0);
    std::shuffle(maze_indices.begin(), maze_indices.end(), urng_);
    // for every square randomly delete a valid edge
    for (int sq : maze_indices) {
        if (ds.size(0) == maze_size) break; // maze connected
        Point grid_idx = ArrToGridIdx(sq, height, width);
        // determine which edges can be removed without causing issues
        vector<int> removable_walls;
        int right_idx = sq+1;
        int down_idx = sq+width;
        if (maze_.at(grid_idx.y).at(grid_idx.x).right
            && right_idx % width != 0 && ds.find(sq) != ds.find(right_idx)) {
            removable_walls.push_back(0);
        }
        if (maze_.at(grid_idx.y).at(grid_idx.x).bottom
            && down_idx < maze_size && ds.find(sq) != ds.find(down_idx)) {
            removable_walls.push_back(1);
        }

        // randomly select wall to remove
        if (removable_walls.size() > 0) {
            int remove_dir = removable_walls.at(urng_() % removable_walls.size());
            setWall(grid_idx.x, grid_idx.y, remove_dir, false);
            switch (remove_dir) {
            case 0: // remove right wall
                ds.setunion(sq, right_idx);
                break;
            case 1: // remove bottom wall
                ds.setunion(sq, down_idx);
                break;
            }
        }
    }
    assert(ds.size(0) == maze_size); // maze is connected
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    maze_.at(y).at(x).GetWall(dir) = exists;
    switch (dir) {
    case 0:
        maze_.at(y).at(x+1).GetWall(2) = exists; // set left wall of right square
        break;
    case 1:
        maze_.at(y+1).at(x).GetWall(3) = exists; // set top wall of bottom square
        break;
    case 2:
        maze_.at(y).at(x-1).GetWall(0) = exists;
        break;
    case 3:
        maze_.at(y-1).at(x).GetWall(1) = exists;
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) {
    if (maze_.at(y).at(x).GetWall(dir)) { // if there is a wall in the dir
        return false;
    }
    // if going in direction goes off grid return false
    switch (dir) {
    case 0:
        if (x+1 >= GetWidth()) return false;
        break;
    case 1:
        if (y+1 >= GetHeight()) return false;
        break;
    case 2:
        if (x-1 < 0) return false;
        break;
    case 3:
        if (y-1 < 0) return false;
        break;
    }
    return true;
}

PNG* SquareMaze::drawMaze() const {
    size_t image_width = GetWidth()*10+1, image_height = GetHeight()*10+1;
    PNG* maze_img = new PNG(image_width, image_height);
    for (size_t x = 10; x < image_width; ++x) { // blacken top row
        HSLAPixel& p = maze_img->getPixel(x, 0);
        p = kBlackPixel_;
    }
    for (size_t y = 0; y < image_height; ++y) { // blacken leftmost column except entrance (0, 0)
        HSLAPixel& p = maze_img->getPixel(0, y);
        p = kBlackPixel_;
    }
    for (int x = 0; x < GetWidth(); ++x) {
        for (int y = 0; y < GetHeight(); ++y) {
            if (maze_.at(y).at(x).right) {
                for (size_t k = 0; k <= 10; ++k) { // idk why I'm doing this but it's what the specification wants
                    HSLAPixel& p = maze_img->getPixel((x+1)*10,y*10+k);
                    p = kBlackPixel_;
                }
            }
            if (maze_.at(y).at(x).bottom) {
                for (size_t k = 0; k <= 10; ++k) { // idk why I'm doing this but it's what the specification wants
                    HSLAPixel& p = maze_img->getPixel(x*10+k,(y+1)*10);
                    p = kBlackPixel_;
                }
            }
        }
    }
    return maze_img;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* img = drawMaze();
    vector<int> soln = solveMaze();
    Point curr(5, 5);
    for (int dir : soln) {
        for (size_t i = 0; i < 10; ++i) {
            HSLAPixel& p = img->getPixel(curr.x, curr.y);
            p = kRedPixel_;
            switch (dir) {
            case 0:
                curr.x++;
                break;
            case 1:
                curr.y++;
                break;
            case 2:
                curr.x--;
                break;
            case 3:
                curr.y--;
                break;
            }
        }
    }
    HSLAPixel& p = img->getPixel(curr.x, curr.y);
    p = kRedPixel_;
    curr.x -= 5;
    curr.y += 5;
    for (size_t k = 1; k <= 9; ++k) {
        HSLAPixel& p = img->getPixel(curr.x+k, curr.y);
        p = kWhitePixel_;
    }
    return img;
}

// SquareMaze private helper functions

int SquareMaze::GetHeight() const {
    return maze_.size();
}

int SquareMaze::GetWidth() const {
    if (maze_.size() == 0) return 0;
    return maze_.at(0).size();
}

void SquareMaze::Clear() {
    maze_.clear();
}

vector<int> SquareMaze::TraceMazeSolnPath(const vector<vector<Location>>& maze_locs, const Location& maze_end) const {
    vector<int> path_directions;
    Location curr = maze_end;
    while (curr.HasPredecessor()) {
        Location pred = maze_locs.at(curr.pred.y).at(curr.pred.x);
        path_directions.push_back(pred.DetermineDirectionTo(curr));
        curr = pred;
    }
    // vector constructed in reverse so it must be reversed
    return vector<int>(path_directions.rbegin(), path_directions.rend());
}

vector<SquareMaze::Point> SquareMaze::FilterValidPts(vector<Point> points, const Location& curr_loc) {
    vector<Point> valid_pts;
    for (const Point& pt : points) {
        if (IsInMazeBounds(pt)) {
            int dir = curr_loc.DetermineDirectionTo(pt);
            if (canTravel(curr_loc.coord.x, curr_loc.coord.y, dir)) {
                valid_pts.push_back(pt);
            }
        }
    }
    return valid_pts;
}

bool SquareMaze::IsInMazeBounds(const Point& p) const {
    return (p.x >= 0) && (p.y >= 0) && (p.x < GetWidth()) && (p.y < GetHeight());
}

SquareMaze::Point SquareMaze::ArrToGridIdx(int arr_idx, int height, int width) const {
    int x = arr_idx % width;
    int y = arr_idx/width;
    return Point(x, y);
}

//////////////////////////////////////
// Location Struct Member Functions //
//////////////////////////////////////

bool SquareMaze::Location::HasPredecessor() {
    return this->pred != Point(-1, -1);
}

vector<SquareMaze::Point> SquareMaze::Location::GetAdjPts(const vector<vector<Location>>& maze_locs) const {
    Point left = this->coord;
    left.x -= 1;
    Point right = this->coord;
    right.x += 1;
    Point up = this->coord;
    up.y -= 1;
    Point down = this->coord;
    down.y += 1;
    return {left, right, up, down};
}

int SquareMaze::Location::DetermineDirectionTo(const Point& pt) const {
    if (pt.x > this->coord.x) { // right movement
        assert(pt.y == this->coord.y);
        return 0;
    } else if (pt.x < this->coord.x) { // left movement
        assert(pt.y == this->coord.y);
        return 2;
    } else if (pt.y > this->coord.y) { // downward movement
        assert(pt.x == this->coord.x);
        return 1;
    } else if (pt.y < this->coord.y) { // upward movement
        assert(pt.x == this->coord.x);
        return 3;
    }
    return 0;
}

int SquareMaze::Location::DetermineDirectionTo(const Location& loc) const {
    return DetermineDirectionTo(loc.coord);
}

std::ostream& operator<<(std::ostream& os, const SquareMaze::Location& loc) {
    os << "Coordinates: " << loc.coord << "\n";
    os << "Distance From Origin: " << loc.dist_from_origin << "\n";
    os << "Predecessor Coordinates: " << loc.pred;
    return os;
}

///////////////////////////////////
// Point Struct Member Functions //
///////////////////////////////////

bool SquareMaze::Point::operator==(const Point& other) const {
    return this->x == other.x && this->y == other.y;
}

bool SquareMaze::Point::operator!=(const Point& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const SquareMaze::Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

////////////////////////////////////
// Square Struct Member Functions //
////////////////////////////////////

bool SquareMaze::Square::operator==(const Square& other) {
    return left == other.left && right == other.right && bottom == other.bottom && top == other.top;
}

bool& SquareMaze::Square::GetWall(int dir) {
    switch (dir) {
    case 0:
        return right;
    case 1:
        return bottom;
    case 2:
        return left;
    case 3:
        return top;
    default:
        return left;
    }
}