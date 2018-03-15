#include "astar_aicomponent.h"
#include <queue>
#include <vector>
#include <functional>
#include <cmath>
class Node
{
    public:
        double cost;
        GameObject go;
        Node(GameObject go, double cost)
        {
            this -> cost = cost;
            this -> go = go;
        }
};

bool Compare(Node n1, Node n2)
{
    return n1.cost < n2.cost;
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
        Node n(*t,distance);
        pq.push(n);
    }
    ObjectPool<Collidable> * retpool;
    for(int i = 0; i < 4; i++)
    {
        Collidable * top = new Collidable();
        top -> Copy(pq.top().go);
        retpool -> pool.push_back(top);
        pq.pop();
    }
    return retpool;
}

void AstarAIComponent::Update(float dt)
{

}

Direction AstarAIComponent::getNextWalkingDirection(float dt)
{
    prioqueue pq(Compare);
    ObjectPool<Collidable> * astar_targets = new ObjectPool<Collidable>();
    if(targets -> pool.size() > 4)
        astar_targets = findTop4Targets(targets -> pool, this->mgo);
    else
        astar_targets = this -> targets;



}
