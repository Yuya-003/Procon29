#include <structure/Field.hpp>

Field::Field(size_t h, size_t w)
{
    for (int i = 0; i < h; i++) {
        this->cells.push_back(std::vector<Cell>(w));
    }
}

void Field::resize(size_t h, size_t w)
{
    this->cells.resize(h);
    for (int i = 0; i < cells.size(); i++) {
        cells[i].resize(w);
        cells[i].shrink_to_fit();
    }
    this->cells.shrink_to_fit();
}

size_t Field::rowSize()
{
    return this->cells[0].size();
}

size_t Field::colSize()
{
    return this->cells.size();
}

int Field::calcScore(Cell::Status status)
{
    int score = 0; //合計していく器
    std::vector<Position> visited;

    if(status == Cell::Status::none){ return 0; }

    for(int i = 0; i < colSize(); i++){
        for(int j = 0; j < rowSize(); j++){

            if(cells[i][j].status == status){ //statusのタイルだったら単純に加算
                score += cells[i][j].point;
            }
            else{ //それ以外のタイル
                bool is_enclosed = true; //囲まれているかのフラグ
                int score_area = 0; //領域ポイント

                if(std::find(visited.begin(), visited.end(), Position(j, i)) != visited.end()){ //探索済みか確認
                    std::queue<Position> queue;

                    queue.push(Position(j, i));
                    while(!queue.empty()){
                        Position p = queue.front();
                        queue.pop();
                        visited.push_back(p);

                        if(is_enclosed){
                            if(p.x == 0 || p.y == 0 || p.x == rowSize()-1 || p.y == colSize()-1){ //フィールドの端なら
                                is_enclosed = false; //囲まれてないです
                            }
                            else{
                                score_area += abs(cells[p.y][p.x].point); //絶対値で加算
                            }
                        }

                        //上→右→下→左 の優先順位で確かめる
                        if(p.y != 0 && cells[p.y-1][p.x].status != status){ //上
                            queue.push(Position(p.x, p.y-1));
                        }

                        if(p.x != rowSize()-1 && cells[p.y][p.x+1].status != status){ //右
                            queue.push(Position(p.x+1, p.y));
                        }

                        if(p.y != colSize()-1 && cells[p.y+1][p.x].status != status){ //下
                            queue.push(Position(p.x, p.y+1));
                        }

                        if(p.x != 0 && cells[p.y][p.x-1].status != status){ //左
                            queue.push(Position(p.x-1, p.y));
                        }
                    }
                }

                if(is_enclosed){
                    score += score_area;
                }
            }
        }
    }

    return score;
}
