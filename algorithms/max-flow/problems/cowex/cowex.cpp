#include<iostream>
#include<algorithm>
#include<limits>
#include<unordered_map>
#include<vector>
using namespace std;

//#ifdef hackpackpp
//Taken from the section on graphs
typedef unordered_map<int,int> umii;
typedef umii::const_iterator edge_iter;
typedef unordered_map<int,umii> umiumii;
typedef umiumii::const_iterator graph_iter;
class graph{
	umiumii g;
	public:
	void insert(int s, int d, int e){g[s][d] = e;g[d];}
	umii::iterator find(int s, int d){ return g.find(s)->second.find(d);}
	edge_iter cbegin(int s)const{return g.find(s)->second.cbegin();}
	edge_iter cend(int s)const{return g.find(s)->second.cend(); }
	graph_iter begin ()const {return g.cbegin();}
	graph_iter end () const {return g.cend();}
	int size()const{return g.size();}
	graph(): g() {};
};
//#endif
int max_flow(graph g, int source, int sink){
	//#ifdef hackpackpp
	//If the source and sink are the same node, then max flow
	if (source == sink) return numeric_limits<int>::max();
	//#ifdef hackpackpp

	//initalize max flow
	//#endif
	int total_flow = 0;

	while(true){
		//#ifdef hackpackpp
		//initialize data structures
		//#endif
		vector<int> flow(g.size() , 0);
		vector<bool> visited(g.size() , false);
		vector<int> previous_node(g.size(), -1);
		//#ifdef hackpackpp

		//initialize the source
		//#endif
		flow[source] = numeric_limits<int>::max();
		//#ifdef hackpackpp

		//Find the widest path in the graph (path of maximal flow)
		//#endif
		int max_flow, max_loc;
		while(true){
			max_flow = 0;
			max_loc = -1;
			//#ifdef hackpackpp

			// find unvistited node with highest capacity O(V) time
			//#endif
			for(auto i = g.begin(); i!=g.end(); i++){
				if( flow[i->first] > max_flow && ! visited[i->first]){
					max_flow = flow[i->first];
					max_loc = i->first;
				}
			}
			//#ifdef hackpackpp

			//No path from source to sink
			//#endif
			if ( max_loc == -1 ){
				break;
			}
			//#ifdef hackpackpp

			//Done! the best node is the sink
			//#endif
			if ( max_loc == sink ){
				break;
			}
			//#ifdef hackpackpp
			//Update the edges leaving the node with the most flow O(1) in sparce graph
			//#endif
			visited[max_loc] = true;
			for (auto i = g.cbegin(max_loc); i != g.cend(max_loc); i++){
				if (flow[i->first] < min(max_flow, i->second)){
					previous_node[i->first] = max_loc;
					flow[i->first] = min(max_flow, i->second);
				}
			}
		}
		//#ifdef hackpackpp

		//There was no remaining path from source to sink
		//#endif
		if (max_loc == -1){
			break;
		}
		//#ifdef hackpackpp

		// update reverse flows
		//#endif
		int pathcapactiy = flow[sink];
		total_flow += pathcapactiy;
		int current_node = sink;
		while (current_node != source){
			int next_node= previous_node[current_node];
			int rev_cap;
			if(g.find(current_node, next_node) == g.cend(current_node)){
				rev_cap = 0;
			} else {
				rev_cap = g.find(current_node,next_node)->second;
			}
			g.insert(next_node, current_node, g.find(next_node, current_node)->second - pathcapactiy);
			g.insert(current_node,next_node, rev_cap + pathcapactiy);
			current_node = next_node;
		}
	}
	return total_flow;
}

//#ifdef hackpackpp

int main(int argc, char *argv[])
{

	int n,s,d,e;
	graph g;
	cin >> n;
	while(n--){
		cin >> s >> d >> e;
		g.insert(s,d,e);
	}
	cin >> s >> d;

	int m = max_flow(g, s, d);

	cout << m << endl;

	return 0;
}
//#endif

