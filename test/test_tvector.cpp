#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length){
	EXPECT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector){
	EXPECT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length){
	EXPECT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector){
    TDynamicVector<int> v(10);

	EXPECT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one){
	TDynamicVector<int> v(10);
	for (int i = 0; i < 10; i++) {
		v[i] = i * i;
	}

	TDynamicVector<int> v0 = v;
	EXPECT_EQ(v, v0);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory){ //мой инглишь блин... тип разная память
	TDynamicVector<int> v0(10);
	for (int i = 0; i < 10; i++) {
		v0[i] = i * i;
	}

	TDynamicVector<int> v1 = v0;
	v1[0] = 121;
	EXPECT_EQ(121, v1[0]);
	EXPECT_EQ(0, v0[0]);
}

TEST(TDynamicVector, can_get_size){
	TDynamicVector<int> v(4);
	EXPECT_EQ(4, v.size()); 
}

TEST(TDynamicVector, can_set_and_get_element){ //а зачем было коментить... я уже ничего не понимаю...
	TDynamicVector<int> v(4);
	v.at(0) = 4;
	EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index){
	TDynamicVector<int> v(4);
	EXPECT_ANY_THROW(v.at(-1) = 0);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index){
	TDynamicVector<int> v(4);
	EXPECT_ANY_THROW(v.at(4) = 0);
}

TEST(TDynamicVector, can_assign_vector_to_itself){
	TDynamicVector<int> v(4);
	EXPECT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(4);
	EXPECT_NO_THROW(v0 = v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(6);
	v1 = v0;
	EXPECT_EQ(v1.size(), v0.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(6);
	EXPECT_NO_THROW(v1 = v0);
}

TEST(TDynamicVector, compare_equal_vectors_return_true){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(4);
	for (int i = 0; i < v0.size(); i++) {
		v0[i] = i;
		v1[i] = i;
	}
	EXPECT_TRUE(v0 == v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true){
	TDynamicVector<int> v(4);
	EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal){ // не работает // работает
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(6);
	EXPECT_FALSE(v0 == v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector){
	TDynamicVector<int> v(4);
	EXPECT_NO_THROW(v + 1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector){
	TDynamicVector<int> v(4);
	EXPECT_NO_THROW(v - 1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector){
	TDynamicVector<int> v(4);
	EXPECT_NO_THROW(v * 7);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(4);
	EXPECT_NO_THROW(v0 + v1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(5);
	EXPECT_ANY_THROW(v0 + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(4);
	EXPECT_NO_THROW(v0 - v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(5);
	EXPECT_ANY_THROW(v0 - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(4);
	EXPECT_NO_THROW(v0 * v1);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size){
	TDynamicVector<int> v0(4);
	TDynamicVector<int> v1(5);
	EXPECT_ANY_THROW(v0 * v1);
}

//мои тесты на move симантику


// довольно скучная вещь, но блин надо...