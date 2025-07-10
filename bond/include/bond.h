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
#include <vector>

#include <calendar.h>

#include <following.h>
#include <cash_flow.h>
#include <frequency.h>
#include <quasi_coupon_schedule.h>


namespace debt_security
{

	template<typename T = double>
	class bond // how bill and bond are related? (is bill a bond?) 
	{

	public:

		explicit bond(
			std::chrono::year_month_day issue_date,
			std::chrono::year_month_day maturity_date, // or should these 2 be captured as a georgian::period?
			fin_calendar::frequency frequency,
			T coupon,
			gregorian::calendar cal, // do we want to copy these everywhere?
			T face = 100 // do we care for this? (or is it just part of price?) if we do not have it we'll have to have cashflow to be based on a unit notional
		) noexcept;

	public:

		auto get_issue_date() const noexcept -> const std::chrono::year_month_day&;
		auto get_maturity_date() const noexcept -> const std::chrono::year_month_day&;
		auto get_frequency() const noexcept -> const fin_calendar::frequency&;
		auto get_coupon() const noexcept -> const T&;
		auto get_calendar() const noexcept -> const gregorian::calendar&;
		auto get_face() const noexcept -> const T&;

	public:

		auto coupon_schedule() const -> gregorian::schedule;
		// this includes all start and end dates

		auto cash_flow() const -> std::vector<fin_calendar::cash_flow<T>>; // should we also return a cashflow at the issuance going the other way? (for that we'll need to capture issue price somehow)
		// is vector a correct data structure to capture the flows?

	private:

		std::chrono::year_month_day issue_date_{};
		std::chrono::year_month_day maturity_date_{};
		fin_calendar::frequency frequency_{};
		T coupon_{};
		gregorian::calendar cal_{};
		T face_{};

	};


	template<typename T>
	bond<T>::bond(
		std::chrono::year_month_day issue_date,
		std::chrono::year_month_day maturity_date,
		fin_calendar::frequency frequency,
		T coupon, // as quoted on the market so 10% is passed in as 10.0 - have not decided yet if is a good idea, or not
		gregorian::calendar cal,
		T face
	) noexcept :
		issue_date_{ std::move(issue_date) },
		maturity_date_{ std::move(maturity_date) },
		frequency_{ std::move(frequency) },
		coupon_{ std::move(coupon) },
		cal_{ std::move(cal) },
		face_{ std::move(face) }
	{
	}


	template<typename T>
	auto bond<T>::get_issue_date() const noexcept -> const std::chrono::year_month_day&
	{
		return issue_date_;
	}

	template<typename T>
	auto bond<T>::get_maturity_date() const noexcept -> const std::chrono::year_month_day&
	{
		return maturity_date_;
	}

	template<typename T>
	auto bond<T>::get_frequency() const noexcept -> const fin_calendar::frequency&
	{
		return frequency_;
	}

	template<typename T>
	auto bond<T>::get_coupon() const noexcept -> const T&
	{
		return coupon_;
	}

	template<typename T>
	auto bond<T>::get_calendar() const noexcept -> const gregorian::calendar&
	{
		return cal_;
	}

	template<typename T>
	auto bond<T>::get_face() const noexcept -> const T&
	{
		return face_;
	}


	template<typename T>
	auto bond<T>::coupon_schedule() const -> gregorian::schedule // do we want to cache this? (and return a const reference?)
	{
		return fin_calendar::make_quasi_coupon_schedule(
			gregorian::util::days_period{ issue_date_, maturity_date_ },
			fin_calendar::duration_variant{ std::chrono::months{ 6 } }, // test only
			issue_date_ // test only
		);
	}


	// should it be called cash_flows? (ot just flows?)
	template<typename T>
	auto bond<T>::cash_flow() const -> std::vector<fin_calendar::cash_flow<T>> // do we want to cache this? (and return a const reference?)
	{
		auto result = std::vector<fin_calendar::cash_flow<T>>{};

		const auto f = fin_calendar::following{};

		const auto& end_dates = coupon_schedule().get_dates();
		for (const auto& end_date : end_dates) // test only - should skip the first date, which is a coupon start date
		{
			const auto payment_date = f.adjust(end_date, cal_); // this must be more elegant with ranges
			result.emplace_back(payment_date, 0.0); // test only
		}

		const auto principal_payment_date = f.adjust(maturity_date_, cal_); // need a more consistent name?
		result.emplace_back(principal_payment_date, face_); // at the moment we handle the coupon and principal payment separately, so we have multiple entries for the same date

		return result;
	}

}
