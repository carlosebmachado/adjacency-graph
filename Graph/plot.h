#pragma once

#include "allegro5/allegro.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#include <string>

#include "graph.h"

#define WIDTH 800
#define HEIGHT 450

ALLEGRO_DISPLAY* window = nullptr;
ALLEGRO_EVENT_QUEUE* eventQueue = nullptr;
ALLEGRO_FONT* font = nullptr;

void error_msg(std::string text) {
    al_show_native_message_box(window, "ERROR",
        "The following error has occurred and the graphic window will be closed: ",
        text.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
}

bool initialize() {
    if (!al_init()) {
        error_msg("Failed to initialize graphics.");
        return false;
    }
    if (!al_init_primitives_addon()) {
        error_msg("Failed to initialize graphics.");
        return false;
    }
    al_init_font_addon();
    if (!al_init_ttf_addon()) {
        error_msg("Failed to initialize fonts.");
        return false;
    }
    if (!al_install_keyboard()) {
        error_msg("Failed to initialize keyboard.");
        return false;
    }

    window = al_create_display(WIDTH, HEIGHT);

    if (!window) {
        error_msg("Failed to create window.");
        return false;
    }

    al_set_window_title(window, "Plot graph");

    font = al_load_font("arial.ttf", 18, 0);
    if (!font) {
        error_msg("Failed to load \"arial.ttf\"");
        al_destroy_display(window);
        return false;
    }

    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        error_msg("Failed to create event queue");
        al_destroy_display(window);
        return false;
    }

    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(window));

    return true;
}

bool checkClose() {
    while (!al_is_event_queue_empty(eventQueue)) {
        ALLEGRO_EVENT alEvent;
        al_wait_for_event(eventQueue, &alEvent);
        if (alEvent.type == ALLEGRO_EVENT_KEY_DOWN)
            if (alEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE) return true;
        else if (alEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return true;
    }
    return false;
}

void drawVertex(std::string id, int x, int y) {
    int p = 5;
    al_draw_circle(x, y, 16, al_map_rgb(0, 0, 0), 2);
    al_draw_text(font, al_map_rgb(0, 0, 0), x-p, y-2*p, 0, id.c_str());
}

void drawEdge(int x1, int y1, int x2, int y2) {
    al_draw_line(x1, y1, x2, y2, al_map_rgb(0, 0, 0), 2);
    al_draw_filled_circle(x1, y1, 14, al_map_rgb(255, 255, 255));
    al_draw_filled_circle(x2, y2, 14, al_map_rgb(255, 255, 255));
}

void plotGraph(Graph graph) {
    bool close = false;
    int key = 0;

    if (not initialize()) {
        return;
    }

    while (not close) {
        al_clear_to_color(al_map_rgb(255, 255, 255));

        close = checkClose();
        std::string gtxt = "Graph: ";
        gtxt += graph.text;
        al_draw_text(font, al_map_rgb(0, 0, 0), 10, 10, 0, gtxt.c_str());
        al_draw_text(font, al_map_rgb(0, 0, 0), 10, 35, 0, "Press ESC to close");
        for (auto v : graph.vertices) {
            for (auto e : v->adjacencies) {
                drawEdge(v->x, v->y, e->x, e->y);
            }
            drawVertex(v->id, v->x, v->y);
        }

        al_flip_display();
    }
    al_destroy_display(window);
    al_destroy_event_queue(eventQueue);
}
