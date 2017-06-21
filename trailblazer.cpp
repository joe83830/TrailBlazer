// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "trailblazer.h"
#include "queue.h"
#include "vector.h"
#include "set.h"

using namespace std;

Vector<Vertex*> depthFirstSearchHelper(BasicGraph& graph, Vertex* start, Vertex* end) {

    if (start == end) {
        Vector<Vertex*> path;
        start->visited = true;
        start->setColor(GREEN);
        path.add(start);
        return path;

    } else {
        start->visited = true;
        for (Vertex* firstInSet : graph.getNeighbors(start)) {

            if (firstInSet->visited == false){
                firstInSet->visited = true;
                Vector<Vertex*> soFar = depthFirstSearchHelper(graph, firstInSet, end); // The path from a specific neighbor to end (assuming that its already complete)

                if (soFar.size() == 0){
                    firstInSet->setColor(GRAY);
                    continue;

                } else {
                    start->setColor(GREEN);
                    soFar.insert(0, start);  // If the path from a specific neighbor to end works, add the current vertex to the path
                    return soFar;
                }
            }
        }
        Vector<Vertex*> empty;  // If no neighbor has a working path, then return an empty vector, indicating that this is a dead end
        return empty;
    }
}

Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {

    graph.resetData();
    Vector<Vertex*> path = depthFirstSearchHelper(graph, start, end);
    return path;
}

//void depthFirstSearchHelper(Vector<Vertex*>& path, const BasicGraph& graph, Vertex* start, Vertex* end, bool& pathFound) {
//    start->visited = true;
//    start->setColor(GREEN);
//    path.add(start);

//    if (start == end) {
//        pathFound = true;
//        return;
//    }

//    for (Vertex* vert : graph.getNeighbors(start)) {
//        if (!vert->visited) {
//            depthFirstSearchHelper(path, graph, vert, end, pathFound);
//            if (pathFound) {
//                return;
//            } else {
//                path.remove(path.size()-1);
//                vert->setColor(GRAY);
//            }
//        }
//    }
//}

//Vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
//    graph.resetData();
//    Vector<Vertex*> path;
//    bool pathFound = false;
//    depthFirstSearchHelper(path, graph, start, end, pathFound);
//    return path;
//}

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {

    graph.resetData();
    Queue<Vertex*> toBeProcessed;
    toBeProcessed.enqueue(start);

    Vertex* theVeryEnd;

    while (true) {
        Vertex* firstInQ = toBeProcessed.dequeue();
        Set<Vertex*> neighbors = graph.getNeighbors(firstInQ);

        int numOfNeighbors = neighbors.size();

        for (int i = 0; i < numOfNeighbors; i++) {
            Vertex* firstInSet = neighbors.first();

            if (firstInSet == end) {
                firstInSet->previous = firstInQ;
                theVeryEnd = firstInSet;

                goto out;
                //break;    // Do I still need this here?

            } else if (firstInSet->visited == false){

                firstInSet->previous = firstInQ;
                firstInSet->visited = true;
                toBeProcessed.enqueue(firstInSet);
            }
            neighbors.remove(firstInSet);
        }
        //        neighbors.mapAll([firstInQ](Vertex* x){x->previous = firstInQ;});
    }
out:

    int count = 0;

    for (Vertex* cur1 = theVeryEnd; cur1 != NULL; cur1 = cur1->previous) {
        count += 1;
    }
    cout << "Count = " << count << endl;
    Vector<Vertex*> path(count);
    Vertex* cur = theVeryEnd;

    for (int i = 0; i < count; i++) {
        path.set(count - i - 1, cur);
        cur = cur->previous;
    }

    return path;
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {



    Vector<Vertex*> path;
    return path;
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Vector<Vertex*> path;
    return path;
}

Set<Edge*> kruskal(BasicGraph& graph) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty set so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    Set<Edge*> mst;
    return mst;
}
