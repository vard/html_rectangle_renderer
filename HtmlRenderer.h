#ifndef __HtmlRenderer_h__
#define __HtmlRenderer_h__
#include <string>
#include <fstream>
#include "Rectangle.h"
#include "inputParser.h"

namespace html_rect_render {

    class HtmlRectangleRenderer {
    public:
        HtmlRectangleRenderer(const Rectangle &workspace, const std::vector<Rectangle> &rectangles);
        void renderToFile(const std::string &fileName);
    private:
        enum SkipMark {
            NO_SKIP = 0,
            SKIP
        };

        static const std::uint32_t kWorkspaceHeight = 400;
        static const std::uint32_t kWorkspaceWidth = 400;

        void scaleRectangles();
        void startHtml();
        void endHtml();
        void startBody();
        void endBody();

        void putTable();
        void putRow(std::uint32_t row);
        void putCell(std::uint32_t row, std::uint32_t column);




        Rectangle workspace_;
        std::vector<Rectangle> rectangles_;
        std::uint32_t nextRectangleIndex_;
        std::vector<std::vector<SkipMark>> skipMarksTable_;
        std::ofstream htmlOutput_;

    };


    HtmlRectangleRenderer::HtmlRectangleRenderer(const Rectangle &workspace, const std::vector<Rectangle> &rectangles)
        : workspace_(workspace),
          rectangles_(rectangles),
          nextRectangleIndex_(0),
          skipMarksTable_(kWorkspaceHeight, std::vector<SkipMark>(kWorkspaceWidth)) {

    }


    void HtmlRectangleRenderer::renderToFile(const std::string &fileName) {
        htmlOutput_ = std::ofstream(fileName, std::ofstream::out | std::ofstream::trunc);
        if(!htmlOutput_.is_open()) {
            throw std::logic_error("error opening output file");
        }

        scaleRectangles();
        startHtml();
        startBody();
        putTable();
        endBody();
        endHtml();

        htmlOutput_.flush();
        htmlOutput_.close();
        //out << coinAnalysisReport->getFalseCoin() << std::endl;
    }

    void HtmlRectangleRenderer::startHtml() {
        htmlOutput_ << "<html>" << std::endl;
    }

    void HtmlRectangleRenderer::endHtml() {
        htmlOutput_ << "</html>" << std::endl;
    }

    void HtmlRectangleRenderer::startBody() {
        htmlOutput_ << "\t<body>" << std::endl;
    }

    void HtmlRectangleRenderer::endBody() {
        htmlOutput_ << "\t</body>" << std::endl;
    }


    void HtmlRectangleRenderer::putTable() {
        htmlOutput_ << "\t\t<table width=\"" << kWorkspaceWidth << "\" height=\"" << kWorkspaceHeight << "\" border=\"0\">" << std::endl;
        for(auto row = 0; row < kWorkspaceHeight; ++row) {
            putRow(row);
        }
        htmlOutput_ << "\t\t</table>" << std::endl;
    }


    void HtmlRectangleRenderer::putRow(std::uint32_t row) {
        htmlOutput_ << "\t\t\t<tr>" << std::endl;
        for(auto cell = 0; cell < kWorkspaceWidth; ++cell) {
            putCell(row, cell);
        }
        htmlOutput_ << "\t\t\t</tr>" << std::endl;
    }


    void HtmlRectangleRenderer::putCell(std::uint32_t row, std::uint32_t column) {
        if(SKIP == skipMarksTable_[row][column]) {
            return;
        }

        htmlOutput_ << "\t\t\t\t<td width=\"1\" height=\"1\" ";
        if(rectangles_.size() > nextRectangleIndex_) {
            auto nextRectangle = rectangles_[nextRectangleIndex_];
            if(nextRectangle.getLeftUpperCorner().y_ == row &&
                    nextRectangle.getLeftUpperCorner().x_ == column) {
                htmlOutput_ << "bgcolor=\"#ffcc00\" colspan=\"" << nextRectangle.getWidth() <<
                            "\" rowspan=\"" << nextRectangle.getHeight() << "\"";

                ++nextRectangleIndex_;

                for(auto skipInRow = row; skipInRow < row + nextRectangle.getHeight(); ++skipInRow) {
                    for(auto skipColumn = column; skipColumn < column + nextRectangle.getWidth(); ++skipColumn) {
                        skipMarksTable_[skipInRow][skipColumn] = SKIP;
                    }
                }
			}
        }

        htmlOutput_ << "></td>" << std::endl;
    }

    void HtmlRectangleRenderer::scaleRectangles() {
        double ratio = std::min(static_cast<double>(kWorkspaceWidth) / static_cast<double>(workspace_.getWidth()),
                                static_cast<double>(kWorkspaceHeight) / static_cast<double>(workspace_.getHeight()));

        std::cout << "scale ratio: " << ratio << std::endl;
        std::for_each(std::begin(rectangles_), std::end(rectangles_), [&](Rectangle & thisRect) {
            thisRect.scale(ratio);
            std::cout << "scaled rect: " << thisRect << std::endl;
        });
    }


} // namespace


#endif // __HtmlRenderer_h__
