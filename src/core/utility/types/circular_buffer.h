#pragma once

#include <array>

namespace rose_core
{
	template <typename T, size_t C>
	class CircularBuffer
		// NOTE: using std::array is fine for small circular queues
		//       will need to use std::vector for larger types and/or queues
	{
	public:
		CircularBuffer();

		const T& getFront(size_t index = 0) const;
		void enqueue(T p_value);
	private:
		std::array<T, C> m_contents{};
		
		size_t m_head = -1;
		size_t m_size = 0; // how many elements currently in the circQueue
	};

	template<typename T, size_t C>
	CircularBuffer<T, C>::CircularBuffer()
	{
	}

	template<typename T, size_t C>
	const T& CircularBuffer<T, C>::getFront(size_t p_index) const
	{
		if (p_index >= C)
		{
			throw std::out_of_range("Circular buffer only stores the last " + std::to_string(C) + " objects, cannot get index " + std::to_string(p_index) + ".");
		}

		if (m_head < 0)
		{
			throw std::out_of_range("Cannot index an empty circular buffer.");
		}

		size_t head = m_head;
		if (head < p_index) head += C;
		return m_contents.at(head - p_index);
	}

	template<typename T, size_t C>
	void CircularBuffer<T, C>::enqueue(T p_value)
	{
		m_head = (m_head + 1) % C;
		m_contents[m_head] = p_value;
	}
}