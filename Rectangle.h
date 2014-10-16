#ifndef __Rectangle_h__
#define __Rectangle_h__


#include <cstdint>
#include <iostream>



namespace html_rect_render{

	struct Point {
		Point(std::uint32_t x, std::uint32_t y)
			:x_(x), y_(y){}
		std::uint32_t x_;
		std::uint32_t y_;
	};


	class Rectangle {
	public:
		Rectangle()
			:leftUpper_(0, 0),
			rightBottom_(0, 0) {}

		Rectangle(std::uint32_t x0, std::uint32_t y0, std::uint32_t x1, std::uint32_t y1)
			:leftUpper_(x0, y0),
			 rightBottom_(x1, y1) {}


		void scale(double ratio) {
			leftUpper_.x_ = static_cast<std::uint32_t>(static_cast<double>(leftUpper_.x_)*ratio);
			leftUpper_.y_ = static_cast<std::uint32_t>(static_cast<double>(leftUpper_.y_)*ratio);
			rightBottom_.x_ = static_cast<std::uint32_t>(static_cast<double>(rightBottom_.x_)*ratio);
			rightBottom_.y_ = static_cast<std::uint32_t>(static_cast<double>(rightBottom_.y_)*ratio);
		}


		std::uint32_t getHeight() const {
			return (rightBottom_.y_ - leftUpper_.y_);
		}


		std::uint32_t getWidth() const {
			return (rightBottom_.x_ - leftUpper_.x_);
		}


		Point getLeftUpperCorner() const {
			return leftUpper_;
		}


		Point getRightBottomCorner() const {
			return rightBottom_;
		}


		friend std::istream& operator>>(std::istream &is, Rectangle& rect);
		friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);


		bool operator<(const Rectangle& other){
			if(this->leftUpper_.y_ < other.leftUpper_.y_) {
				return true;
			} else if (this->leftUpper_.y_ == other.leftUpper_.y_) {
				return (this->leftUpper_.x_ < other.leftUpper_.x_);
			}
			return false;
		}


	private:
		Point leftUpper_;
		Point rightBottom_;
	};


	std::istream& operator>>(std::istream& is, Rectangle& rect) {
		is >> rect.leftUpper_.x_ >> rect.leftUpper_.y_ >> rect.rightBottom_.x_ >> rect.rightBottom_.y_;
		return is;
	}


	std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
		os << "(" << rect.leftUpper_.x_ << ", " << rect.leftUpper_.y_ << ") (" 
		          << rect.rightBottom_.x_ << ", " << rect.rightBottom_.y_ << ")";
		return os;
	}


} // namespace

#endif // __Rectangle_h__
