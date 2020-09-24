#pragma once

#include <string>
#include "graph.hpp"

void drawVertex(std::string id, int x, int y) {
//    int p = 5;
//    al_draw_circle(x, y, 16, al_map_rgb(0, 0, 0), 2);
//    al_draw_text(font, al_map_rgb(0, 0, 0), x-p, y-2*p, 0, id.c_str());
}

void drawEdge(int x1, int y1, int x2, int y2) {
//    al_draw_line(x1, y1, x2, y2, al_map_rgb(0, 0, 0), 2);
//    al_draw_filled_circle(x1, y1, 14, al_map_rgb(255, 255, 255));
//    al_draw_filled_circle(x2, y2, 14, al_map_rgb(255, 255, 255));
}

void plotGraph(Graph graph) {
//    bool close = false;
//    int key = 0;

//    if (not initialize()) {
//        return;
//    }

//    while (not close) {
//        al_clear_to_color(al_map_rgb(255, 255, 255));

//        close = checkClose();
//        std::string gtxt = "Graph: ";
//        gtxt += graph.text;
//        al_draw_text(font, al_map_rgb(0, 0, 0), 10, 10, 0, gtxt.c_str());
//        al_draw_text(font, al_map_rgb(0, 0, 0), 10, 35, 0, "Press ESC to close");
//        for (auto v : graph.vertices) {
//            for (auto e : v->adjacencies) {
//                drawEdge(v->x, v->y, e->x, e->y);
//            }
//            drawVertex(v->id, v->x, v->y);
//        }

//        al_flip_display();
//    }
//    al_destroy_display(window);
//    al_destroy_event_queue(eventQueue);
}
