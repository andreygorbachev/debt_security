// The MIT License (MIT)
//
// Copyright (c) 2025 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <chrono>
#include <utility>


namespace price
{

	template<typename T = double>
	class price final
	{

	public:

		explicit price(
			std::chrono::year_month_day settlement_date,
			T settlement_price,
			T face = 100
		) noexcept;

	public:

		auto get_settlement_date() const noexcept -> const std::chrono::year_month_day&;
		auto get_settlement_price() const noexcept -> const T&;
		auto get_face() const noexcept -> const T&;

	private:

		std::chrono::year_month_day settlement_date_{};
		T settlement_price_{};
		T face_{};

	};


	template<typename T>
	price<T>::price(
		std::chrono::year_month_day settlement_date,
		T settlement_price,
		T face
	) noexcept :
		settlement_date_{ std::move(settlement_date) },
		settlement_price_{ std::move(settlement_price) },
		face_{ std::move(face) }
	{
	}


	template<typename T>
	auto price<T>::get_settlement_date() const noexcept -> const std::chrono::year_month_day&
	{
		return settlement_date_;
	}

	template<typename T>
	auto price<T>::get_settlement_price() const noexcept -> const T&
	{
		return settlement_price_;
	}

	template<typename T>
	auto price<T>::get_face() const noexcept -> const T&
	{
		return face_;
	}

}
