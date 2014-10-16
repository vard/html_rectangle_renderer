#ifndef __inputParser_h__
#define __inputParser_h__

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "rectangle.h"

namespace html_rect_render {


    class InputParser {
    public:
        InputParser(const std::string &filename);
        Rectangle getWorkspaceRectangle();
        std::vector<Rectangle> getRectangles();;

    private:
        std::vector<Rectangle> rectangles_;
        //std::uint32_t minX_;
        std::uint32_t maxX_;
        //std::uint32_t minY_;
        std::uint32_t maxY_;
    };


    InputParser::InputParser(const std::string &filename)
        :// minX_(0),
        maxX_(0),
        // minY_(0),
        maxY_(0) {
        std::ifstream input(filename, std::ifstream::in);
        if(!input.is_open()) {
            throw std::logic_error("error opening input file");
        }

        bool thisIsFirstRect = true;
        while(!input.eof()) {
            Rectangle newRect;
            input >> newRect;

            std::cout << newRect << std::endl;
            if(thisIsFirstRect) {
                //minX_ = newRect.getLeftUpperCorner().x_;
                maxX_ = newRect.getRightBottomCorner().x_;
                //minY_ = newRect.getLeftUpperCorner().y_;
                maxY_ = newRect.getRightBottomCorner().y_;
                thisIsFirstRect = false;
            } else {
                /*if(minX_ > newRect.getLeftUpperCorner().x_) {
                    minX_ = newRect.getLeftUpperCorner().x_;
                }*/
                if(maxX_ < newRect.getRightBottomCorner().x_) {
                    maxX_ = newRect.getRightBottomCorner().x_;
                }
                /*
                if(minY_ > newRect.getLeftUpperCorner().y_) {
                    minY_ = newRect.getLeftUpperCorner().y_;
                }*/
                if(maxY_ < newRect.getRightBottomCorner().y_) {
                    maxY_ = newRect.getRightBottomCorner().y_;
                }
            }

            rectangles_.push_back(std::move(newRect));
        }

        /*std::cout << "Min x: " << minX_ << std::endl;
        std::cout << "Min y: " << minY_ << std::endl;*/
        std::cout << "Workspace: " << getWorkspaceRectangle() << std::endl;
        // std::cout << "Max y: " << maxY_ << std::endl;


        std::sort(std::begin(rectangles_), std::end(rectangles_));
    }


    Rectangle InputParser::getWorkspaceRectangle() {
        return Rectangle(0, 0, maxX_, maxY_);
    }


    std::vector<Rectangle> InputParser::getRectangles() {
        return rectangles_;
    }


} // namespace

#endif // __inputParser_h__
