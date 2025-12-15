#include <graphics.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

class Ball {
public:
    float x, y;
    float vx, vy;
    int r, color;

    Ball(float px, float py, float pvx, float pvy) {
        x = px;
        y = py;
        vx = pvx;
        vy = pvy;
        r = 15;
        color= rand()%15 + 1;
    }

    void update() {
        x = x + vx;
        y = y + vy;

        if (x - r < 0 || x + r > getmaxx())
            vx = -vx;

        if (y - r < 0 || y + r > getmaxy())
            vy = -vy;
    }

    void draw() {
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        fillellipse(x, y, r, r);

    }
};

void collision(Ball &a, Ball &b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float jarak = sqrt(dx*dx + dy*dy);

    if (jarak < a.r + b.r) {
        // tukar arah
        float temp;

        temp = a.vx; a.vx = b.vx; b.vx = temp;
        temp = a.vy; a.vy = b.vy; b.vy = temp;
    }
}

class Quadtree {
public:
    int x, y, w, h;
    vector<Ball*> data;
    Quadtree* child[4];

    Quadtree(int px, int py, int pw, int ph) {
        x = px; y = py; w = pw; h = ph;
        for (int i=0;i<4;i++) child[i] = NULL;
    }

    void clear() {
        data.clear();
        for (int i=0;i<4;i++) {
            if (child[i]) {
                child[i]->clear();
                delete child[i];
                child[i] = NULL;
            }
        }
    }

    void split() {
        int hw = w/2;
        int hh = h/2;

        child[0] = new Quadtree(x, y, hw, hh);
        child[1] = new Quadtree(x+hw, y, hw, hh);
        child[2] = new Quadtree(x, y+hh, hw, hh);
        child[3] = new Quadtree(x+hw, y+hh, hw, hh);
    }

    void insert(Ball* b) {
        if (child[0] == NULL && data.size() > 5) {
            split();
        }

        data.push_back(b);
    }

    void getAll(vector<Ball*>& out) {
        for (int i=0;i<data.size();i++)
            out.push_back(data[i]);

        for (int i=0;i<4;i++) {
            if (child[i])
                child[i]->getAll(out);
        }
    }
};

int main() {
    initwindow(800,600);
    srand(time(NULL));

    vector<Ball> bola;
    for (int i=0;i<70;i++) {
        bola.push_back(
            Ball(rand()%800, rand()%600,
                 (rand()%5)+1, (rand()%5)+1)
        );
    }

    bool quadtreeMode = false;

    while (true) {
        if (kbhit()) {
            if (getch() == ' ')
                quadtreeMode = !quadtreeMode;
        }

        cleardevice();

        for (int i=0;i<bola.size();i++)
            bola[i].update();

        if (!quadtreeMode) {
            for (int i=0;i<bola.size();i++) {
                for (int j=i+1;j<bola.size();j++) {
                    collision(bola[i], bola[j]);
                }
            }
        } else {
            Quadtree qt(0,0,800,600);

            for (int i=0;i<bola.size();i++)
                qt.insert(&bola[i]);

            vector<Ball*> list;
            qt.getAll(list);

            for (int i=0;i<list.size();i++) {
                for (int j=i+1;j<list.size();j++) {
                    collision(*list[i], *list[j]);
                }
            }
        }

        for (int i=0;i<bola.size();i++)
            bola[i].draw();

        if (quadtreeMode)
            outtextxy(10,10,"QUADTREE");
        else
            outtextxy(10,10,"BRUTEFORCE");

        delay(10);
    }
}
