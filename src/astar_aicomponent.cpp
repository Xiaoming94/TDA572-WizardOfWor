#include "astar_aicomponent.h"
#include <queue>
#include <vector>
#include <functional>
#include <cmath>

bool Compare(Node n1, Node n2)
{
    return n1.cost < n2.cost;
}

bool TargetChecker::CheckCloseEnough(double x, double y)
{
    for (GameObject t : targets)
    {
        bool closeH = std::abs(x - t.horizontalPosition) < 3;//Horizontally close
        bool closeY = std::abs(y - t.verticalPosition) < 3;
        if (closeH || closeY)
            return true;
    }
    return false;
}

typedef std::priority_queue<Node,std::vector<Node>,std::function<bool(Node,Node)>> prioqueue;


/**
 * Helper function, finds the top 4 closest enemy to object
 * First calculating the distance of all the targets to the object.
 * Add them to a priority Queue and than Pops the first 4 elements.
 * And return them in another vector
 */
ObjectPool<Collidable> * findTop4Targets(std::vector<Collidable*> targets, MovingGameObject * object)
{
    prioqueue pq(Compare);
    for(Collidable * t : targets)
    {
        double dx = t -> horizontalPosition - object -> horizontalPosition;
        double dy = t -> verticalPosition - object -> verticalPosition;
        double distance = sqrt(dx * dx + dy * dy);// Calculating distance using pythagorean theorem
        Node n(t->horizontalPosition, t->verticalPosition, distance);
        pq.push(n);
    }
    ObjectPool<Collidable> * retpool;
    for(int i = 0; i < 4; i++)
    {
        Collidable * top = new Collidable();
        const Node topNode = pq.top();
        top -> horizontalPosition = topNode.x;
        top -> verticalPosition = topNode.y;
        retpool -> pool.push_back(top);
        pq.pop();
    }
    return retpool;
}

void AstarAIComponent::Update(float dt)
{

}

Direction AstarAIComponent::getNextWalkingDirection(float change)
{
    prioqueue pq(Compare);
    ObjectPool<Collidable> * astar_targets = new ObjectPool<Collidable>();
    if(targets -> pool.size() > 4)
        astar_targets = findTop4Targets(targets -> pool, this->mgo);
    else
        astar_targets = this -> targets;
    TargetChecker tc(astar_targets);
    double currentX = mgo -> horizontalPosition;
    double currentY = mgo -> verticalPosition;
    Direction nextDir = Direction::NONE;
    Direction lastAction = Direction::NONE;
    Node currentNode(currentX,currentY,0);

    while(!tc.CheckCloseEnough(currentX,currentY))
    {
        // Expand node if not close enough to a target.
        PossibleDirections dirs = MovingComponent::GetPossibleDirs(change);

        //Get Heuristics for each neighbour if You can go there
        HeuristicVec hvec = h.movement(dirs, astar_targets, mgo -> horizontalPosition, mgo -> verticalPosition, change);
        double val_up = hvec.at(0);
        double val_left = hvec.at(1);
        double val_down = hvec.at(2);
        double val_right = hvec.at(3);

        //Add all available neighbours to Queue;
        if (dirs.up && lastAction != Direction::DOWN)
        {
            Node n(currentX, currentY - change, double(currentNode.cost + val_up + 1));
            std::vector<Direction> newPaths(currentNode.path);
            newPaths.push_back(Direction::UP);
            n.path = newPaths;
            pq.push(n);
        }

        if (dirs.left && lastAction != Direction::RIGHT)
        {
            Node n(currentX - change, currentY, double(currentNode.cost + val_left + 1));
            std::vector<Direction> newPaths(currentNode.path);
            newPaths.push_back(Direction::LEFT);
            n.path = newPaths;
            pq.push(n);

        }

        if (dirs.down && lastAction != Direction::UP)
        {
            Node n(currentX, currentY + change, double(currentNode.cost + val_down + 1));
            std::vector<Direction> newPaths(currentNode.path);
            newPaths.push_back(Direction::DOWN);
            n.path = newPaths;
            pq.push(n);
        }

        if (dirs.right && lastAction != Direction::LEFT)
        {
            Node n(currentX + change, currentY, double(currentNode.cost + val_right + 1));
            std::vector<Direction> newPaths(currentNode.path);
            newPaths.push_back(Direction::RIGHT);
            n.path = newPaths;
            pq.push(n);
        }

        currentNode = pq.top();
        pq.pop();
        currentX = currentNode.x;
        currentY = currentNode.y;
        nextDir = currentNode.path.front();
        lastAction = currentNode.path.back();

    }

    return nextDir;


}
