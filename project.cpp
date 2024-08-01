#include<iostream>
#include<string>
using namespace std;


const string ORANGE = "\033[38;2;255;165;0m";
const string RESET = "\033[0m";


//node struct represent a vertex in a graph
struct node
{
	int city_name;
	bool air_status;
	node* next;

	//constructor
	node(int c, int a)
	{
		city_name = c;
		air_status = a;
		next = nullptr;
	}
};

//queue
struct Queue
{
	node* front;
	node* rear;

	// Constructor
	Queue()
	{
		front = nullptr;
		rear = nullptr;
	}

	// Push function
	void push(int e)
	{
		node* temp = new node(e, 0);
		if (rear == nullptr)
		{
			front = rear = temp;
		}
		else
		{
			rear->next = temp;
			rear = temp;
		}
	}

	// Pop function
	void pop()
	{
		if (!isempty())
		{
			node* temp = front;
			front = front->next;
			if (front == nullptr) // Queue is empty now
			{
				rear = nullptr;
			}
			delete temp;
		}
	}

	// Peek function
	int peek()
	{
		if (!isempty())
		{
			return front->city_name;
		}
		return -1; // Return a value indicating empty
	}

	// Empty function
	bool isempty()
	{
		return front == nullptr;
	}

	// Destructor
	~Queue()
	{
		while (!isempty())
		{
			pop();
		}
	}
};

// reverse the queue
void reverse_queue(Queue& q)
{
	if (q.isempty())
	{
		return;
	}

	int frontElement = q.peek();  // remove the front element
	q.pop();

	reverse_queue(q);  // reverse the remaining queue

	// add the removed element to the rear of the reversed queue
	q.push(frontElement);
}


//struct graph 
struct Graph
{
	//N=number of stops
	int N;
	node** links;

	//constructor
	Graph(int n)
	{
		N = n;

		//allocating heap memory
		links = new node * [N];

		int i = 0;
		//setting pointers to nullptr and at same time linking cities by road
		while (i < N)
		{
			links[i] = nullptr;

			if (i != (N - 1))
			{
				add_edge(i, i + 1, 0);
			}
			i++;
		}

	}

	//add edge to graph function
	void add_edge(int from, int to, int a)
	{
		int distance = to - from;

		if (distance < 0)
		{
			distance = -distance;
		}

		if (a == 1 && distance <= 6)
		{
			// Skip adding the air route if the distance between from and to is not greater than 6
			return;
		}

		//creating vertex
		//here (a) is the status of  the link is it by air(1) or not(0)
		node* temp = new node(to, a);

		//adding new node at start of links(list) of the given city(from)
		temp->next = links[from];
		links[from] = temp;
	}

	//BFS and shortest path
	void shortest_path(int max_hours)
	{
		// declaring visited array and queue
		int* visited = new int[N];
		Queue queue;

		// putting all index to zero
		for (int i = 0; i < N; i++)
		{
			visited[i] = 0;
		}

		// marking first city 1 as true and pushing it in queue
		visited[0] = 1;
		queue.push(0);

		node* curr = nullptr;
		int p = 1;

		while (!queue.isempty())
		{
			p = queue.peek() + 1;
			queue.pop();

			curr = links[p - 1];

			while (curr)
			{
				if (!visited[curr->city_name])
				{
					visited[curr->city_name] = p;
					queue.push(curr->city_name);
				}

				curr = curr->next;
			}
		}

		output(visited, max_hours);

		// free the dynamically allocated array
		delete[] visited;
	}

	//print the graph
	void print()
	{
		node* curr = nullptr;

		//for loop control links array
		for (int i = 0; i < N; i++)
		{
			//pointing curr to first node in linklist of a city(i)
			curr = links[i];

			if (curr)
			{
				cout << "			   " << i + 1 << " -> ";

				//here while loop control the list of each city
				while (curr)
				{
					cout << curr->city_name + 1;
					if (curr->air_status)
					{
						cout << " (air)";
					}
					else
					{
						cout << " (road)";
					}

					curr = curr->next;
					if (curr)
					{
						cout << " , ";
					}
				}
				cout << endl;
			}

			else
			{
				cout << "			   " << i + 1 << " (DESTINATION)";
			}
			curr = nullptr;
		}
	}

	//graph destructor
	~Graph()
	{

		node* temp = nullptr;
		node* curr = nullptr;

		//for loop control links(array)
		for (int i = 0; i < N; i++)
		{
			curr = links[i];
			//while control node links(list)
			while (curr)
			{
				temp = curr;
				//delete node at start of list
				curr = curr->next;
				delete temp;
			}
		}
		//delete array(links)
		delete[]links;
	}





	//output generation
	void output(int arr[], int max_hours)
	{
		//vriables declare
		int index = 0, number = 0;
		index = N - 1;

		//result queue store shortest path
		Queue result;
		Queue result2;
		string final_result = "";

		//while loop untill start city 1 reached, generate result in reverse order
		while (1)
		{
			//loop exit when index reached 0
			if (arr[index] == 1 && index == 0)
			{
				result.push(index + 1);
				result2.push(index + 1);
				break;
			}

			number = arr[index] - 1;
			result.push(index + 1);

			result2.push(index + 1);
			index = number;
		}

		//reversing queue to get correct output
		reverse_queue(result);
		reverse_queue(result2);

		// total_hours store final time taken
		int total_hours = 0;
		node* curr = nullptr;
		int city_num = 0, city_num2 = 0;


		//loop continue untill queue is empty
		while (!result.isempty())
		{
			//first peek top element in city_num from queue then pop it from the queue 
			city_num = result.peek() - 1;
			curr = links[city_num];

			result.pop();

			if (!result.isempty())
			{
				//first peek top element in city_num from queue after previous element is poped
				city_num2 = result.peek() - 1;

				//find city_num2 is links of city_num(index)
				while (curr)
				{
					if (curr->city_name == city_num2)
					{
						// Calculate distance as the difference between city_num2 and city_num
						int distance = city_num2 - city_num;

						// Determine the time for the route based on the distance and edge type
						if (curr->air_status)
						{
							if (distance > 6)
							{
								total_hours += 24;  // Air route
							}
							else
							{
								total_hours += 4;   // Road route
							}
						}
						else
						{
							total_hours += 4;   // Road route
						}
					}

					curr = curr->next;
				}
			}
		}

		int total_days = total_hours / 24;
		int remaining_hours = total_hours % 24;


		// display names of stops in path traversal
		cout << "The Shortest Path to reach the destination is : " << endl;
		cout << ORANGE;
		while (!result2.isempty())
		{
			cout << result2.peek() << " -> ";
			result2.pop();
		}
		cout << RESET;
		cout << endl;


		cout << endl << "The equipment will be delivered in : " << ORANGE << total_days << " days and " << remaining_hours << " hours" << RESET << endl << endl;

		if (total_hours <= max_hours)
		{
			cout << "Congrats, the delivery " << ORANGE << "CAN" << RESET << " be made within the assigned time of " << max_hours / 24 << " days and " << max_hours % 24 << " hours." << endl;
		}
		else
		{
			cout << "Unfortunately, the delivery" << ORANGE << "CAN NOT" << RESET << " be made within the assigned time of " << max_hours / 24 << " days and " << max_hours % 24 << " hours." << endl;
		}

	}

};

//convert function convert string to int
void convert(string input, int numbers[])
{
	int num = 0;
	//j for array index
	int j = 0;

	//for loop till end of string
	for (int i = 0; input[i] != '\0'; i++)
	{
		//if space comes it will store it in a array other wise calculate the number befor space
		if (input[i] != ' ')
		{
			num = (num * 10) + (input[i] - '0');
		}
		else
		{
			if (j < 2)
			{
				numbers[j] = num;
				j++;
			}
			num = 0;
		}
	}
	//store last number in an array
	if (j < 2)
	{
		numbers[j] = num;
	}
}

//valid_input checks if input given is valid or not
bool valid_input(string input, int spaces)
{
	bool valid = 1;
	char check;
	int count_space = 0;

	for (int i = 0; input[i] != '\0'; i++)
	{
		//checks for spaces
		if (input[i] == ' ')
		{
			count_space++;
			if ((count_space > spaces))
			{
				cout << "Only enter numbers as needed" << endl;
				valid = 0;
				break;
			}
		}

		//check for only numbers in the string or not
		if ((input[i] >= '0' && input[i] <= '9') || (input[i] == ' '))
		{

		}
		else
		{
			if (input[i] == '-' || input[i] == '+' || input[i] == '*' || input[i] == '/')
			{
				cout << "do not enter any operator" << endl;
			}
			else
			{
				cout << "Only enter numbers" << endl;
			}
			valid = 0;
			break;
		}
	}

	if ((count_space < spaces))
	{
		cout << "Only enter numbers as needed" << endl;
		valid = 0;
	}

	return valid;
}

//case_solve solve each test case graph
void case_solve(string input, int number[])
{
	//aerial_routes stores max number of air routes in graph, N stores max stop number
	int routes_air = 0;
	int N = 0;
	int again_inp = 1, i = 0;
	int max_days = 0;
	int max_hours = 0;

	//loops to again ask for input after invalid previous input
	while (again_inp)
	{
		input = "";
		//taking input for number of max stops(N)
		cout << "Enter number of stops : ";
		getline(cin, input);

		if (valid_input(input, 0))
		{
			convert(input, number);
			N = number[0];

			if (N)
			{
				while (again_inp)
				{
					input = "";
					number[0] = 0;
					number[1] = 0;

					//taking input for total number of aerial_routes in the graph
					cout << "Enter number of routes by air : ";
					getline(cin, input);

					if (valid_input(input, 0))
					{
						convert(input, number);
						routes_air = number[0];

						input = "";
						number[0] = 0;
						number[1] = 0;
						again_inp = 0;
					}
				}
			}
			else
			{
				cout << "Enter number of cities greater than 0" << endl;
			}
		}
	}

	again_inp = 1;
	//making graph containing stops(N)
	Graph graph(N);

	//loops to again ask for input after invalid previous input
	while (again_inp)
	{
		if (i < routes_air)
		{
			//taking input for stops and air routes 
			getline(cin, input);

			if (valid_input(input, 1))
			{
				convert(input, number);
				if ((number[0] <= (N) && number[0] > 0) && (number[1] <= (N) && number[1] > 0) && (number[0] != number[1]))
				{
					graph.add_edge(number[0] - 1, number[1] - 1, 1);
					i++;
				}
				else if (number[0] == number[1])
				{
					cout << "Source and destination city can not be same" << endl;
				}
				else
				{
					cout << "Enter number greater then zero or less then " << N << endl;
				}
				input = "";
				number[0] = 0;
				number[1] = 0;
			}
		}
		else
		{
			again_inp = 0;
		}
	}

	while (true)
	{
		input = "";
		cout << "Enter the max days and hours for delivery : ";
		getline(cin, input);

		if (valid_input(input, 1))
		{
			convert(input, number);
			max_days = number[0];
			max_hours = number[1];

			if (max_days >= 0 && max_hours >= 0 && max_hours < 24)
			{
				break;
			}
			else
			{
				cout << "Enter a non-negative number of days and hours between 0 and 23" << endl;
			}
		}
	}

	int total_max_hours = max_days * 24 + max_hours;

	cout << endl;
	cout << "#####################################################################################\n";
	cout << "#####################################################################################\n";
	cout << "###                                                                               ###\n";
	cout << "###                                                                               ###\n";
	cout << "###                        " << ORANGE << "GRAPH OF LINKS BETWEEN STOPS" << RESET << "                           ###\n";
	cout << "###                           " << ORANGE << "( BY ROAD AND BY AIR )" << RESET << "                              ###\n";
	cout << "###                                                                               ###\n";
	cout << "###                                                                               ###\n";
	cout << "#####################################################################################\n";
	cout << "#####################################################################################\n";
	cout << endl;
	cout << RESET;
	graph.print();
	cout << endl << endl;

	graph.shortest_path(total_max_hours);
}

int main()
{

	cout << ORANGE;
	cout << " _____             _____          ______          ______   _______  _   ______ ______  _   ______  _____ \n";
	cout << "|      \\        / |      |\\    |    |     |      |      | |        | | |         |    | | |       |      \n";
	cout << "|       \\      /  |      | \\   |    |     |      |      | |  ____  | | |_____    |    | | |       |____  \n";
	cout << "|_____   \\    /   |_____ |  \\  |    |     |      |      | | |    | | |       |   |    | | |            | \n";
	cout << "|         \\  /    |      |   \\ |    |     |      |      | | |    | | |       |   |    | | |            | \n";
	cout << "|_____     \\/     |_____ |    \\|    |     |_____ |______| |______| |_| ______|   |    |_| |______ _____|	\n\n\n";
	cout << RESET;

	//number array used to store numbers when convert from string to int
	int number[] = { 0,0 };
	string input = "";

	//enter number of cases
	int cases = 0;
	while (1)
	{
		cout << "Enter number of Test cases = ";
		getline(cin, input);

		if (valid_input(input, 0))
		{
			//convert string to int
			convert(input, number);

			if (number[0] != 0)
			{
				cases = number[0];
				break;
			}
			else
			{
				cout << "Enter number greater then zero" << endl;
			}
		}
	}

	//call case_solve function for number of cases
	for (int i = 0; i < cases; i++)
	{
		input = "";
		number[0] = 0;
		number[1] = 0;

		//calling case_solve function
		cout << "Test case " << i + 1 << endl;
		case_solve(input, number);
		cout << endl;
	}

	return 0;
}



// air route backwards (DONE)
// air route less than 6 (DONE)
// air route equal to 6 (DONE)
// air route greater than 6 (DONE)
// input Validation of Day and Hours (DONE)
// input Validation of Air Routes (DONE)
// calculation of Time (DONE)
// display Graph (DONE)
// display Shortest Path (DONE)

