#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "math.h"
using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

class Point{
    public:
        int x, y;
        
        Point(int x, int y){
            this->x=x;
            this->y=y;
        }
        float distance2(Point p) {
            return (x - p.x)*(x - p.x) + (y - p.y)*(y - p.y);
        }
        float distance(Point p){
            return sqrt(distance2(p));
        }
        
        bool operator==(const Point& rhs) const { return (this->x == rhs.x && this->y == rhs.y);}
    
        friend ostream& operator<<(ostream& os, Point const & tc) {
            return os << tc.x<< " "<<tc.y << endl;
        }
    
};

int main()
{
    bool boostAvailable=true;
    
    int thrust=100;
    
    vector<Point> checkpoints;
    
    Point* prevCheckpoint = NULL;
    Point* nextCheckpoint = NULL;
    bool lapIsPassed = false;
    bool turnToNextCheck = false;
    bool slowDown = false;
    int checkPointIndex = 1;
    int prevCheckpointDist;
    // game loop
    while (1) {
        int x;
        int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        
        int opponentX;
        int opponentY;
        cin >> opponentX >> opponentY; cin.ignore();
        
        cerr<<"thrust = "<<thrust<<endl;
        cerr<<"angle = "<<nextCheckpointAngle<<endl;
        
        if (nextCheckpoint == NULL){
            nextCheckpoint = new Point(nextCheckpointX, nextCheckpointY);
            checkpoints.push_back(*nextCheckpoint);
        }
        ///////////////////////
        if (!lapIsPassed){
            if (nextCheckpointX != nextCheckpoint->x || nextCheckpointY != nextCheckpoint->y){
                cerr<<"checkpointchanged"<<endl;
                slowDown=false;
                nextCheckpoint = new Point(nextCheckpointX, nextCheckpointY);
                
                if(checkpoints.front() == *nextCheckpoint) {
                    lapIsPassed = true;
                    for (auto c:checkpoints)
                        cerr<<c<<" "<<endl;
                    checkPointIndex = 1;
                    cerr<<"lap is passed" <<endl;
                }
                else{
                    cerr<<"add checkpoint"<<endl;
                    cerr<<"checkpoint added "<<nextCheckpoint->x << " "<<nextCheckpoint->y<<endl;
                    checkpoints.push_back(*nextCheckpoint);
                    checkPointIndex++;
                }
            } 
        }
        else{
            cerr<<"nextcheck in "<<nextCheckpointDist<<" m"<<endl;
            if (nextCheckpointX != nextCheckpoint->x || nextCheckpointY != nextCheckpoint->y){
                slowDown=false;
                turnToNextCheck=false;
                nextCheckpoint = &checkpoints[checkPointIndex];
                checkPointIndex++;
                cerr<<"next checkpoint "<<checkpoints[checkPointIndex]<<endl;
                if (checkPointIndex == checkpoints.size()){
                    checkPointIndex=0;
                }
            }
            if (!turnToNextCheck && thrust>50 && nextCheckpointAngle>= -3 && nextCheckpointAngle <= 3
            &&nextCheckpointDist < 2500){
                cerr<<"turning to nextcheck "<< checkPointIndex<<endl;
                turnToNextCheck=true;
            }
            cerr<<prevCheckpointDist<<" "<<nextCheckpointDist<<endl;
            if (prevCheckpointDist < nextCheckpointDist){
                turnToNextCheck=false;
            }
        }
        
        
        prevCheckpointDist=nextCheckpointDist;
        
        if (nextCheckpointDist < 3000){
            slowDown=true;
        }
        if (!slowDown){
            if (nextCheckpointAngle >= 0 && nextCheckpointAngle < 45){
                thrust=100;
            } 
            else if (nextCheckpointAngle > -45 && nextCheckpointAngle < 0)
                thrust=100;
            else
                thrust=50;
                
             if (nextCheckpointAngle > -10 && nextCheckpointAngle < 10 && nextCheckpointDist > 7000
        && thrust > 80 && boostAvailable==true){
                boostAvailable=false;
                cout << nextCheckpointX << " " << nextCheckpointY << " " << "BOOST" << endl;
                cerr<<"BOOST is used"<<endl;
                continue;
            }
           
        }
        else{
            thrust-=5;
            if (thrust <= 50)
                thrust += 50;
        }
        
        if (turnToNextCheck == true){
            cerr<<"went to next check "<< checkPointIndex<<endl;
            
            cout<<checkpoints[checkPointIndex].x <<" "<<checkpoints[checkPointIndex].y<<" "<< thrust << endl;
            continue;
        }
       
        cout << nextCheckpointX << " " << nextCheckpointY << " " << thrust << endl;
        
        /*if (nextCheckpointDist > 1000 && nextCheckpointDist < 2000){
            cerr<<"slowing down";
            thrust--;
            cout << nextCheckpointX << " " << nextCheckpointY << " " << thrust << endl;
            continue;
        }*/
    }
}
        
        
        
        
