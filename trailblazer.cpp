// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "trailblazer.h"
#include "queue.h"
#include "vector.h"
#include "set.h"
#include "pqueue.h"
#include "strlib.h"

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

Vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {

    graph.resetData();
    Queue<Vertex*> toBeProcessed;
    toBeProcessed.enqueue(start);
    start->setColor(YELLOW);

    Vertex* theVeryEnd;

    while (true) {

        Vertex* firstInQ = toBeProcessed.dequeue();
        firstInQ->setColor(GREEN);
        firstInQ->visited = true;
        Set<Vertex*> neighbors = graph.getNeighbors(firstInQ);

        for (Vertex* firstInSet : neighbors) {

            if (firstInSet == end) {
                firstInSet->previous = firstInQ;
                theVeryEnd = firstInSet;
                goto out;

            } else if (firstInSet->visited == false){

                firstInSet->previous = firstInQ;
                firstInSet->visited = true;
                toBeProcessed.enqueue(firstInSet);
                firstInSet->setColor(YELLOW);
            }
        }
        //        neighbors.mapAll([firstInQ](Vertex* x){x->previous = firstInQ;});
    }
out:

    int count = 0;
    for (Vertex* cur1 = theVeryEnd; cur1 != NULL; cur1 = cur1->previous) {
        count += 1;
    }
    Vector<Vertex*> path(count);
    Vertex* cur = theVeryEnd;

    for (int i = 0; i < count; i++) {
        path.set(count - i - 1, cur);
        cur = cur->previous;
    }
    return path;
}

Vector<Vertex*> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {

    graph.resetData();
    PriorityQueue<Vertex*> toBeRanked;

    start->cost = 0;
    toBeRanked.enqueue(start, start->cost);
    start->setColor(YELLOW);
    Vertex* theVeryEnd;

    while(toBeRanked.size() != 0) {

        Vertex* firstInQ = toBeRanked.dequeue();
        firstInQ->setColor(GREEN);
        firstInQ->visited = true;

        if (firstInQ == end) {
            theVeryEnd = firstInQ;
            break;

        } else {
            Set<Vertex*> neighbors = graph.getNeighbors(firstInQ);

            for (Vertex* firstInSet : neighbors) {
                double altKosten = firstInSet->cost;
                Edge* bridge = graph.getEdge(firstInQ, firstInSet);
                double neuKosten = firstInQ->cost + bridge->cost;

                if (firstInSet->visited == false && altKosten == 0) {
                    firstInSet->cost = neuKosten;
                    firstInSet->previous = firstInQ;
                    firstInSet->setColor(YELLOW);
                    toBeRanked.enqueue(firstInSet, firstInSet->cost);

                } else if (firstInSet->visited == false && altKosten != 0 && neuKosten < altKosten){
                    firstInSet->cost = neuKosten;
                    firstInSet->previous = firstInQ;
                    firstInSet->setColor(YELLOW);
                    toBeRanked.changePriority(firstInSet, firstInSet->cost);
                }
            }
        }
    }

    int count = 0;
    for (Vertex* cur1 = theVeryEnd; cur1 != NULL; cur1 = cur1->previous) {
        count += 1;
    }

    Vector<Vertex*> path(count);
    Vertex* cur = theVeryEnd;

    for (int i = 0; i < count; i++) {
        path.set(count - i - 1, cur);
        cur = cur->previous;
    }
    return path;
}

Vector<Vertex*> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {

    graph.resetData();
    PriorityQueue<Vertex*> toBeRanked;

    start->cost = 0;
    toBeRanked.enqueue(start, start->cost);
    start->setColor(YELLOW);
    Vertex* theVeryEnd;

    while(toBeRanked.size() != 0) {

        Vertex* firstInQ = toBeRanked.dequeue();
        firstInQ->setColor(GREEN);
        firstInQ->visited = true;

        if (firstInQ == end) {
            theVeryEnd = firstInQ;
            break;

        } else {
            Set<Vertex*> neighbors = graph.getNeighbors(firstInQ);

            for (Vertex* firstInSet : neighbors) {
                double altKosten = firstInSet->cost;
                Edge* bridge = graph.getEdge(firstInQ, firstInSet);
                double heurKosten = heuristicFunction(firstInSet, end);
                double neuKosten = firstInQ->cost + bridge->cost + heurKosten;

                if (firstInSet->visited == false && altKosten == 0) {
                    firstInSet->cost = neuKosten;
                    firstInSet->previous = firstInQ;
                    firstInSet->setColor(YELLOW);
                    toBeRanked.enqueue(firstInSet, firstInSet->cost);

                } else if (firstInSet->visited == false && altKosten != 0 && neuKosten < altKosten){
                    firstInSet->cost = neuKosten;
                    firstInSet->previous = firstInQ;
                    firstInSet->setColor(YELLOW);
                    toBeRanked.changePriority(firstInSet, firstInSet->cost);
                }
            }
        }
    }

    int count = 0;
    for (Vertex* cur1 = theVeryEnd; cur1 != NULL; cur1 = cur1->previous) {
        count += 1;
    }

    Vector<Vertex*> path(count);
    Vertex* cur = theVeryEnd;

    for (int i = 0; i < count; i++) {
        path.set(count - i - 1, cur);
        cur = cur->previous;
    }
    return path;
}

Set<Edge*> kruskal(BasicGraph& graph) {

    graph.resetData();
    cout << "Started" << endl;
    Set<Vertex*> allVertexes = graph.getVertexSet();
    Set<string> setOfClusters;

    for (Vertex* curVertex : allVertexes) {
        cout << "entered for loop" << endl;
        string nameOfVert = curVertex->name;
        setOfClusters.add(nameOfVert);
    }
    cout << "exited for loop" << endl;
    Set<Edge*> allEdges = graph.getEdgeSet();
    PriorityQueue<Edge*> prioritizedEdges;

    for (Edge* curEdge : allEdges){
        cout << "Setting pq" << endl;
        prioritizedEdges.enqueue(curEdge, curEdge->cost);
    }
    cout << "PQ is all set" << endl;

    Set<Edge*> mst;
    while (setOfClusters.size() > 1) {
        cout << "Entered While loop" << endl;
        cout << "size of cluster" << setOfClusters.size() << endl;
        Edge* examinedEdge = prioritizedEdges.dequeue();

        Vertex* startingVert = examinedEdge->start;
        string nameOfStart = startingVert->name;

        Vertex* endingVert = examinedEdge->end;
        string nameOfEnd = endingVert->name;

        string lookingInto;
        string lookingInto2;

        for (string curName : setOfClusters) {
            if (stringContains(curName, nameOfStart)) {
                lookingInto = curName;
                break;
            }
        }

        if (!stringContains(lookingInto, nameOfEnd)) {

            for (string curName : setOfClusters) {
                if (stringContains(curName, nameOfEnd)) {
                    lookingInto2 = curName;
                    break;
                }
            }
            string newCluster = lookingInto + lookingInto2;
            setOfClusters.remove(lookingInto);
            setOfClusters.remove(lookingInto2);
            setOfClusters.add(newCluster);
            mst.add(examinedEdge);
        }
    }
    cout << "Exited while loop" << endl;

    return mst;
}
