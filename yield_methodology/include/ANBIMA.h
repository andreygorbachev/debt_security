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

#include <resets_math.h>

#include <calculation_252.h>

#include <bill.h>
#include <bond.h>
#include <quote.h>


namespace debt_security
{

	template<typename T = double>
	class ANBIMA final // better name?
	{

	public:

		auto price(
			const T& yield,
			const bill<T>& bill,
			const quote<T>& quote
		) const -> T;

		// is this what we want? (the same yield methodology for both bill and bond)
		// they are the same at the level of the cashflows I think, so maybe methodology
		// should be taking cashflows rather than bill or bond?
		// or templated?
		// (we often have a special yield calculations in the last period of the bond, so we should capture that nicely)
		auto price(
			const T& yield,
			const bond<T>& bond,
			const quote<T>& quote
		) const -> T;

	};


	template<typename T>
	auto ANBIMA<T>::price(
		const T& yield,
		const bill<T>& bill,
		const quote<T>& quote
	) const -> T
	{
		const auto cf = bill.cash_flow();
		const auto dc = fin_calendar::calculation_252{ bill.get_calendar() };
		const auto yf = dc.fraction(quote.get_settlement_date(), cf.get_payment_date()); // should be truncated to 14 decimal places
		// we should probably note that end date would give the same year fraction as the end date is not included in the period
		// and hence unadjusted end date, or following adjusted end date would give the same number of business days

		const auto price = quote.get_face() / pow(T{ 1 } + yield, yf); // should we use amount from the cashflow?

		const auto& truncate = quote.get_truncate(); // assuming that 14 decimal places from above will be hard coded, should this also be hard coded?
		if (truncate)
			return reset::trunc_dp(price, *truncate);
		else
			return price;
	}


	template<typename T>
	auto ANBIMA<T>::price(
		const T& yield,
		const bond<T>& bond,
		const quote<T>& quote
	) const -> T
	{
		const auto cfs = bond.cash_flow();

		const auto dc = fin_calendar::calculation_252{ bond.get_calendar() };

		auto price = T{ 0 };
		for (const auto& cf : cfs)
		{
			const auto yf = dc.fraction(quote.get_settlement_date(), cf.get_payment_date()); // should be truncated to 14 decimal places
			// we should probably note that end date would give the same year fraction as the end date is not included in the period
			// and hence unadjusted end date, or following adjusted end date would give the same number of business days

			price += cf.get_amount() / pow(T{ 1 } + yield, yf); // we should sum up the amounts on the same date first
			// there is also a rounding of each discounted value
		}

		const auto& truncate = quote.get_truncate(); // assuming that 14 decimal places from above will be hard coded, should this also be hard coded?
		if (truncate)
			return reset::trunc_dp(price, *truncate);
		else
			return price;
	}

}
