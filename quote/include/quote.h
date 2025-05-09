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
#include <optional>


namespace debt_security
{

	template<typename T = double>
	class quote final // should we call it quotation_methodology?
	{

	public:

		explicit quote(
			std::chrono::year_month_day settlement_date,
			T face = 100,
			std::optional<unsigned int> truncate = std::nullopt
		) noexcept;

	public:

		auto get_settlement_date() const noexcept -> const std::chrono::year_month_day&;
		auto get_face() const noexcept -> const T&;
		auto get_truncate() const noexcept -> const std::optional<unsigned int>&;

	private:

		std::chrono::year_month_day settlement_date_{};
		T face_{};
		std::optional<unsigned int> truncate_{};

	};


	template<typename T>
	quote<T>::quote(
		std::chrono::year_month_day settlement_date,
		T face,
		std::optional<unsigned int> truncate
	) noexcept :
		settlement_date_{ std::move(settlement_date) },
		face_{ std::move(face) },
		truncate_{ std::move(truncate) }
	{
	}


	template<typename T>
	auto quote<T>::get_settlement_date() const noexcept -> const std::chrono::year_month_day&
	{
		return settlement_date_;
	}

	template<typename T>
	auto quote<T>::get_face() const noexcept -> const T&
	{
		return face_;
	}

	template<typename T>
	auto quote<T>::get_truncate() const noexcept -> const std::optional<unsigned int>&
	{
		return truncate_;
	}

}
