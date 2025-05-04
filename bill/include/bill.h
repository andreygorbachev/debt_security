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

#include <calendar.h>

#include <cash_flow.h>


namespace bill
{

	template<typename T = double>
	class bill
	{

	public:

		explicit bill(
			std::chrono::year_month_day issue_date,
			std::chrono::year_month_day maturity_date, // or should these 2 be captured as a georgian::period?
			gregorian::calendar cal, // do we want to copy these everywhere?
			T face = 100 // do we care for this? (or is it just part of price?) if we do not have it we'll have to have cashflow to be based on a unit notional
		) noexcept;

	public:

		auto get_issue_date() const noexcept -> const std::chrono::year_month_day&;
		auto get_maturity_date() const noexcept -> const std::chrono::year_month_day&;
		auto get_calendar() const noexcept -> const gregorian::calendar&;
		auto get_face() const noexcept -> const T&;

	public:

		auto cashflow() const -> cash_flow::cash_flow<T>; // should we also return a cashflow at the issuance going the other way? (for that we'll need to capture issue price somehow)
		// should it be called cash_flow()?

	private:

		std::chrono::year_month_day issue_date_{};
		std::chrono::year_month_day maturity_date_{};
		gregorian::calendar cal_{};
		T face_{};

	};


	template<typename T>
	bill<T>::bill(
		std::chrono::year_month_day issue_date,
		std::chrono::year_month_day maturity_date,
		gregorian::calendar cal,
		T face
	) noexcept :
		issue_date_{ std::move(issue_date) },
		maturity_date_{ std::move(maturity_date) },
		cal_{ std::move(cal) },
		face_{ std::move(face) }
	{
	}


	template<typename T>
	auto bill<T>::get_issue_date() const noexcept -> const std::chrono::year_month_day&
	{
		return issue_date_;
	}

	template<typename T>
	auto bill<T>::get_maturity_date() const noexcept -> const std::chrono::year_month_day&
	{
		return maturity_date_;
	}

	template<typename T>
	auto bill<T>::get_calendar() const noexcept -> const gregorian::calendar&
	{
		return cal_;
	}

	template<typename T>
	auto bill<T>::get_face() const noexcept -> const T&
	{
		return face_;
	}


	template<typename T>
	auto bill<T>::cashflow() const -> cash_flow::cash_flow<T> // do we want to cache this? (and return a const reference?)
	{
		return cash_flow::cash_flow<T>{ maturity_date_, face_ }; // should be adjusted for a good payment date
	}

}
