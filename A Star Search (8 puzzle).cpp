#include<bits/stdc++.h>
using namespace std;

//node class
struct node
{
    vector<int> orientation;
    int g_cost, h_cost, f_cost;
    node* parent;

    node()
    {
        g_cost = 0;
        h_cost = 0;
        f_cost = 0;
        parent = NULL;
    }
};

//operator overloading for priority_queue
struct comp
{
    bool operator()(const node* lhs, const node* rhs) const
    {
        return lhs->f_cost > rhs->f_cost;
    }
};

int no_of_elements;
vector<int> goal_test;
vector<node*> already_explored;
priority_queue<node*, vector<node*>, comp> to_be_explored;

//print board
void print_board(node* n)
{
    int dim = sqrt(no_of_elements);
    int k = 0;
    for(int i = 0; i < dim; ++i)
    {
        for(int j = 0; j < dim; ++j)
            cout << n->orientation[k++] << " ";
        cout << endl;
    }
    cout << endl;
}

//print solution
void reconstruct_path_from_root_to_goal(node* n)
{
    node* temp = n;
    vector<node*> totalpath;	//it's a list for containing all the nodes in the path from the root to the goal
    while(temp != NULL)
    {
        totalpath.push_back(temp);
        temp = temp->parent;
    }

    int sz = totalpath.size();
    //print number of moves required
    cout << "Moves Required: " << sz-1 << endl;

    //show the moves one by one
    for(int i = sz-1; i >= 0; --i)
        print_board(totalpath[i]);
}

//calculate heuristic
int calculate_misplaced_tiles(node* n)
{
    int cnt = 0;
    for(int i = 0; i < no_of_elements; ++i)
        if(goal_test[i] != n->orientation[i])
            ++cnt;

    return cnt;
}

//build successor node
node* create_successor_node(node* state, int pos1, int pos2)
{
    node* new_state = new node();
    new_state->orientation = state->orientation;
    swap(new_state->orientation[pos1], new_state->orientation[pos2]);
    new_state->h_cost = calculate_misplaced_tiles(new_state);
    new_state->g_cost = state->g_cost+1;
    new_state->f_cost = new_state->h_cost + new_state->g_cost;
    new_state->parent = state;

    return new_state;
}

//generate successors
vector<node*> get_successor(node* n)
{
    int pos, row, col, dim;
    for(int i = 0; i < no_of_elements; ++i)
    {
        if(n->orientation[i] == 0)
        {
            pos = i;
            break;
        }
    }
    dim = sqrt(no_of_elements);
    row = pos / dim;
    col = pos % dim;

    vector<node*> successors;

    if(col != 0)
        successors.push_back(create_successor_node(n, pos, pos-1));

    if(col != dim-1)
        successors.push_back(create_successor_node(n, pos, pos+1));

    if(row != 0)
        successors.push_back(create_successor_node(n, pos, pos-dim));

    if(row != dim-1)
        successors.push_back(create_successor_node(n, pos, pos+dim));

    return successors;
}

//return true if goal
bool is_Goal(node* n)
{
    return (n->h_cost == 0) ? 1 : 0;
}

bool check_already_explored_list(node* n)
{
    int sz = already_explored.size(), j;
    for(int i = 0; i < sz; ++i)
    {
        for(j = 0; j < no_of_elements; ++j)
        {
            if(n->orientation[j] != already_explored[i]->orientation[j])
                break;
        }
        if(j == no_of_elements)
            return 1;
    }
    return 0;
}

void A_star_search(node* n)
{
    n->h_cost = calculate_misplaced_tiles(n);
    n->f_cost = n->h_cost;
    n->parent = NULL;
    to_be_explored.push(n);

    bool flag;
    int tentative_g_cost, sz, k;
    node *current, *temp;
    vector<node*> current_successors;
    priority_queue<node*, vector<node*>, comp> pq;

    while(!to_be_explored.empty())
    {
        current = to_be_explored.top();
        to_be_explored.pop();
        already_explored.push_back(current);

        if(is_Goal(current))
        {
            reconstruct_path_from_root_to_goal(current);
            return;
        }

        current_successors.clear();
        current_successors = get_successor(current);

        sz = current_successors.size();
        for(int i = 0; i < sz; ++i)
        {
            if(check_already_explored_list(current_successors[i]))
                continue;
            tentative_g_cost = current->g_cost+1;

            while(!pq.empty())
                pq.pop();
            while(!to_be_explored.empty())
            {
                temp = to_be_explored.top();
                to_be_explored.pop();

                flag = 0;
                for(k = 0; k < no_of_elements; ++k)
                    if(current_successors[i]->orientation[k] != temp->orientation[k])
                        break;
                if(k == no_of_elements)
                    flag = 1;


                if(flag && tentative_g_cost < temp->g_cost)
                {
                    temp->parent = current;
                    temp->g_cost = tentative_g_cost;
                    temp->f_cost = temp->g_cost + temp->h_cost;
                }
                pq.push(temp);
            }
            if(!flag)
                pq.push(current_successors[i]);
            to_be_explored = pq;
        }
    }

    return;
}

int main()
{
    int x;
    node* new_node = new node();

    cin >> no_of_elements;
    for(int i = 0; i < no_of_elements; ++i)
    {
        cin >> x;
        new_node->orientation.push_back(x);
    }

    for(int i = 0; i < no_of_elements; ++i)
    {
        cin >> x;
        goal_test.push_back(x);
    }

    A_star_search(new_node);
}

/*
9
2 4 3 7 1 5 0 8 6
1 2 3 4 5 6 7 8 0
*/
