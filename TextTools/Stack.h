#pragma once

//partner class that only exists to provide datatype for Stack
class point {
public:
    int x, y;
};

//creates stack of all of the points that the ship has since traveled to
class Stack {
public:
    point arr[1000];
    int H; //head
    void push(int x, int y) {
        arr[H].x = x;
        arr[H].y = y;
        H++; //move to empty space
    }
    point pop() {
        H--; //move down to top
        return arr[H];
    }
    point peek() { //show top point without moving head ("deleting" it)
        return arr[H - 1];
    }
};