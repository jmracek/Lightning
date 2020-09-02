#include "Singleton.hpp"

/* What are my requirements???

- The type of the task should allow me to uniquely retrieve the object (singleton)
- How does the user encode the graph structure in the Workflow type?
    - Workflow< Task<T1, TypeList<D1, ..., Dn>>, ... >
    - Workflow< Node<Tk>, Edge<Ti, Tj> >
- I should not need to know T's downstream tasks in order to retrieve the corresponding T& in the workflow
*/

// Simplest example... T1 -> T2
// Workflow<T1, TypeList<T2>, T2, TypeList<>>
/* What is my interface for Task<T, TList>?
*   Task::instance() <- Problem. I need to be able to call instance() knowing only T and not TList
*/

template<typename T>
class Node<T>: public Singleton<T> {};

template<typename T, typename... Args>
class Task<T, TypeList<Args...> >:
    public Node<T>,
    public Visitable<T>,
    public GenerateDownstreamTasks<Args...> {
};

template<typename... Args>
class GenerateDownstreamArgs;

template<typename T, typename... Args>
class GenerateDownstreamArgs<T, Args...>:
    public DependencyFor<T>,
    public GenerateDownstreamArgs<Args...> {
};

template<typename T>
class GenerateDownstreamArgs<>:
    public NullType {
};

template<typename T>
class DependencyFor<T> {
public:
    T& nextTask_;
};


#ifndef WORKFLOW_HPP
#define WORKFLOW_HPP

template<
    template<class...> TraversalPolicy = AsyncTraversal,
    typename... Args
>
class Workflow<TraversalPolicy, Args...>:
    public TraversalPolicy<Args...>,
    public Workflow<Args...>






template<typename T, typename TList, typename... Args>
class Workflow<T, TList, Args...>:
    public Task<T, TList>,
    public Workflow<Args...> {
};

#endif




dispatch() {
    // visitor.accept
    // Decrement the counter.  Check if it's zero. 
    // If it is, run the next task.  If not, return.
}

/* Possible designs
    1. Have a workflow be a typelist of types T, such that a task T subtypes Q if and only if Q must be completed before T.
 What kind of workflow behaviour do I want to encapsulate in policy classes? 
    - Dispatch policy (Async, Sync, etc.)
    - How to specify a workflow or task?

        class Task:
            public DependencyFor<Task2>,
            ...
            public DependencyFor<TaskN> {...};

        class Task:
            public DependensOn<Task2>,
            ...
            public DependensOn<TaskN> {...};

        Workflow<DispatchPolicy, task1, typelist<t1,...,tk>, task2, typelist<...>>

        template<typename P, typename T, typename TList, typename Args...>
        WorkflowVisitor< Workflow<P, T, TList, Args...>>:
            public VisitorPolicy<T>,
            public Visitor<Args...> {};

    - How do I want to implement workflow traversal? I think this is the most important question.

DispatchPolicy::dispatch(Visitor&, Visitable&) {
    node.accept(visitor);
     
}

Two major questions:
    1) How do I specify dependencies between tasks by encoding that information in the types?
    2) How can I implement work dispatching in a policy class?


class A: Visitable<A>

template<typename T, typename TList>
class Task {
std::atomic<int> counter_ = Length<TList>::value;
};

Suppose I have a type, Task<T, TList>, where TList represents the tasks that are downstream of T.
How does T know when it is able to be executed?

I could do this one of two ways.
    1) "Workflow forwards"
    class Task:
        public DependencyFor<Task2>,
        ...
        public DependencyFor<TaskN> {...};
    2) "Workflow backwards"
    class Task:
        public DependensOn<Task2>,
        ...
        public DependensOn<TaskN> {...};




       




*/
