#include <search/BasicSearch.hpp>

BasicSearch::BasicSearch()
{
}

std::array<Behavior, 2> BasicSearch::search(Field field)
{
    std::vector<std::vector<Node>> map(field.colSize(), std::vector<Node>(field.rowSize(), Node()));

    std::vector<Node> nodes;
    for(int k = 0; k <= 1; k++){

        Node goal;
        goal.cell.point = 1e-6;
        for(int i = 0; i < field.colSize(); i++){
            for(int j = 0; j < field.rowSize(); j++){
                map[i][j].cell = field.cells[i][j];
                map[i][j].status = Node::Status::none;
                map[i][j].p = Position(j, i);

                if(map[i][j].cell.status==Cell::none && (map[i][j].cell.point >= goal.cell.point || (map[i][j].cell.point >= border_score && map[i][j].cell.point >= goal.cell.point))){
                    goal = map[i][j];
                }
            }
        }

        Position player_pos = field.team1[k];
        map[player_pos.y][player_pos.x].parent = nullptr;
        map[player_pos.y][player_pos.x].cost = 0;
        map[player_pos.y][player_pos.x].h_cost = sqrt(pow(goal.p.x-player_pos.x, 2) + pow(goal.p.y-player_pos.y, 2));
        map[player_pos.y][player_pos.x].score = map[player_pos.y][player_pos.x].h_cost
                                                + map[player_pos.y][player_pos.x].cost
                                                - map[player_pos.y][player_pos.x].cell.point;
        
        nodes.push_back(map[player_pos.y][player_pos.x]);
        while(!nodes.empty()){
            Node node = nodes[0];
            for(int i = 1; i < nodes.size(); i++){
                if(node.score < nodes[i].score){
                    node = nodes[i];
                }
            }

            //以下にいろいろ追加

        }

    }

    //とりあえずなんかリターン
    std::array<Behavior, 2> behavior;
    behavior[0].action = Behavior::Action::stay;
    behavior[0].dir = Behavior::Dir::none;
    behavior[1].action = Behavior::Action::stay;
    behavior[1].dir = Behavior::Dir::none;
    return behavior; 
}
