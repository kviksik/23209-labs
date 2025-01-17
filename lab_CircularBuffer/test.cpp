#include <gtest/gtest.h>
#include "CBuff.h"

TEST(CircularBuffTests, DefaultConstructor) {
	CircularBuffer buffer;

	EXPECT_TRUE(buffer.empty());
}// по умолчанию

TEST(CircularBuffTests, CopyConstructor) {
	CircularBuffer buffer(5, 'a');
	CircularBuffer buffer_copy(buffer);

	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(buffer[i], buffer_copy[i]);
	}
}

TEST(CircularBuffTests, SetThecapacity) {
	CircularBuffer buffer(5);

	EXPECT_EQ(buffer.capacity(), 5);
	EXPECT_TRUE(buffer.empty());
}// Конструирует буфер заданной ёмкости

TEST(CircularBuffTests, FillTheConctruction) {
	CircularBuffer buffer(7, 'a');

	EXPECT_EQ(buffer.capacity(), 7);
	EXPECT_EQ(buffer.size(), 7);
	EXPECT_EQ(buffer.size(), buffer.capacity());
	EXPECT_FALSE(buffer.empty());
	for (int i = 0; i < 7; ++i) {
		EXPECT_EQ(buffer[i], 'a');
	}
}// целиком заполняет его элементом elem.

TEST(CircularBuffTests, IndexOperator) {
	CircularBuffer buf(3);
	buf.push_back('a');
	buf.push_back('b');
	buf.push_back('c');

	EXPECT_EQ(buf[0], 'a');
	EXPECT_EQ(buf[1], 'b');
	EXPECT_EQ(buf[2], 'c');
}//Доступ по индексу

TEST(CircularBuffTests, IndexAtt) {
	CircularBuffer buf(5, 'a');

	EXPECT_EQ(buf[0], 'a');
	EXPECT_EQ(buf[4], 'a');
	EXPECT_THROW(buf.at(5), std::out_of_range);
}//Доступ по индексу. Методы бросают исключение

TEST(CircularBuffTests, LinkToFront) {
	CircularBuffer buf(3);
	buf.push_back('a');
	buf.push_back('b');
	buf.push_back('c');

	EXPECT_EQ(buf.front(), 'a');
}//Ссылка на первый элемент.

TEST(CircularBuffTests, LinkToBack) {
	CircularBuffer buf(3);
	buf.push_back('a');
	buf.push_back('b');
	buf.push_back('c');

	EXPECT_EQ(buf.back(), 'c');
}//Ссылка на последний элемент.

TEST(CircularBuffTests, RotateBuffer) {
	CircularBuffer buf(4);

	buf.push_back('r');
	buf.push_back('d');
	buf.push_back('w');
	buf.push_back('o');

	buf.rotate(2);

	EXPECT_EQ(buf[0], 'w');
	EXPECT_EQ(buf[1], 'o');
	EXPECT_EQ(buf[2], 'r');
	EXPECT_EQ(buf[3], 'd');

}//Сдвигает буфер

TEST(CircularBuffTests, BuffSize) {
	CircularBuffer buf1(3, 'a');
	EXPECT_EQ(buf1.size(), 3);

	CircularBuffer buf2(10);
	EXPECT_EQ(buf2.size(), 0);

	CircularBuffer buf3(5);
	buf3.push_back('a');
	buf3.push_back('b');
	EXPECT_EQ(buf3.size(), 2);
}//Количество элементов, хранящихся в буфере.

TEST(CircularBuffTests, IsEmpty) {
	CircularBuffer buf(3, 'a');

	EXPECT_FALSE(buf.empty());
	buf.clear();
	EXPECT_TRUE(buf.empty());

	CircularBuffer buf2(3);
	EXPECT_TRUE(buf2.empty());
}//Пустота буфера

TEST(CircularBuffTests, IsFull) {
	CircularBuffer buf(1);

	EXPECT_FALSE(buf.full());
	buf.push_back('a');
	EXPECT_TRUE(buf.full());
}//true, если size() == capacity()

TEST(CircularBuffTests, LotOfReserve) {
	CircularBuffer buf(3, 'a');

	EXPECT_EQ(buf.reserve(), 0);
	buf.pop_back();
	EXPECT_EQ(buf.reserve(), 1);
}//Количество свободных ячеек в буфере.

TEST(CircularBuffTests, Bufcapacity) {
	CircularBuffer buf(3, 'a');

	EXPECT_EQ(buf.capacity(), 3);
	buf.pop_back();
	EXPECT_EQ(buf.capacity(), 3);
}//Ёмкость буфера

TEST(CircularBuffTests, SetCapacity) {
	CircularBuffer buf(3, 'a');

	buf.set_capacity(10);
	EXPECT_EQ(buf.capacity(), 10);
	EXPECT_EQ(buf.size(), 3);

}//set_capacity

TEST(CircularBuffTests, Resize) {
	CircularBuffer buf(3, 'a');

	EXPECT_EQ(buf.size(), 3);

	buf.resize(2, 'a');
	EXPECT_EQ(buf.size(), 2);
}//Изменяет размер буфера.resize

TEST(CircularBuffTests, AssigmentOperator) {
	CircularBuffer buf_1(3);
	buf_1.push_back('a');
	buf_1.push_back('b');

	CircularBuffer buf_2 = buf_1;

	EXPECT_EQ(buf_1[0], 'a');
	EXPECT_EQ(buf_2[1], 'b');
	EXPECT_EQ(buf_2.size(), 2);
}//Оператор присваивания.operator=

TEST(CircularBuffTests, BuffSwap) {
	CircularBuffer buf1(3, 'a');
	CircularBuffer buf2(4);
	buf2.push_back('b');
	buf2.push_back('c');

	buf1.swap(buf2);
	EXPECT_EQ(buf1.size(), 2);
	EXPECT_EQ(buf2.size(), 3);
}//Обменивает содержимое буфера с буфером cb.swap

TEST(CircularBuffTests, PushBack) {
	CircularBuffer buf(3);

	buf.push_back('a');
	EXPECT_EQ(buf.back(), 'a');

	buf.push_back('b');
	EXPECT_EQ(buf.back(), 'b');

	EXPECT_EQ(buf.size(), 2);
}//Добавляет элемент в конец буфера. push

TEST(CircularBuffTests, PushFront) {
	CircularBuffer buf(2);

	buf.push_front('a');
	buf.push_front('b');

	EXPECT_EQ(buf.front(), 'b');
	EXPECT_EQ(buf.back(), 'a');

}//Добавляет новый элемент перед первым элементом буфера. 

TEST(CircularBuffTests, PopBack) {
	CircularBuffer buf(2);

	buf.push_back('a');
	buf.push_back('b');

	buf.pop_back();

	EXPECT_EQ(buf.back(), 'a');
	EXPECT_EQ(buf.size(), 1);
}//удаляет последний элемент буфера.pop

TEST(CircularBuffTests, PopFront) {
	CircularBuffer buf(2);

	buf.push_back('a');
	buf.push_back('b');

	buf.pop_front();

	EXPECT_EQ(buf.front(), 'b');
	EXPECT_EQ(buf.size(), 1);
}//удаляет первый элемент буфера. 

TEST(CircularBuffTests, InsertAnElement) {
	CircularBuffer buf(4);
	buf.push_back('a');
	buf.push_back('b');
	buf.push_back('c');

	buf.insert(1, 'd');
	EXPECT_EQ(buf[0], 'a');
	EXPECT_EQ(buf[1], 'd');
	EXPECT_EQ(buf[2], 'b');
	EXPECT_EQ(buf[3], 'c');
	EXPECT_EQ(buf.size(), 4);
}//Вставляет элемент item по индексу pos insert

TEST(CircularBuffTests, Erase) {
	CircularBuffer buf(5);
	buf.push_back('a');
	buf.push_back('b');
	buf.push_back('c');
	buf.push_back('d');
	buf.push_back('e');

	//EXPECT_EQ(buf.erase(1, 10), std::out_of_range);
	buf.erase(1, 3);

}//Удаляет элементы из буфера в интервале. erase

TEST(CircularBuffTests, ClearTheBuff) {
	CircularBuffer buf(5, 'a');

	buf.clear();
	EXPECT_EQ(buf.size(), 0);
	EXPECT_EQ(buf.capacity(), 5);
	EXPECT_TRUE(buf.empty());
}//Очищает буфер. clear

TEST(CircularBuffTests, SameBuffers) {
	CircularBuffer buf_1(5);
	buf_1.push_back('a');

	CircularBuffer buf_2(5);
	buf_2.push_back('b');

	CircularBuffer buf_3(5);
	buf_3.push_back('a');

	EXPECT_TRUE(buf_1 == buf_3);
	EXPECT_FALSE(buf_1 == buf_2);

	buf_3.push_back('b');
	EXPECT_FALSE(buf_1 == buf_3);
	EXPECT_FALSE(buf_2 == buf_3);

}//bool operator==

TEST(CircularBuffTests, NotSameBuffers) {
	CircularBuffer buf_1(5);
	buf_1.push_back('a');

	CircularBuffer buf_2(5);
	buf_2.push_back('b');

	CircularBuffer buf_3(5);
	buf_3.push_back('a');

	EXPECT_TRUE(buf_1 != buf_2);
	EXPECT_FALSE(buf_1 != buf_3);
}//bool operator!=

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
