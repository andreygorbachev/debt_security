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

#include <bill.h>
#include <price.h>


namespace yield
{

	template<typename T = double>
	class ANBIMA final // better name?
	{

	public:

		auto price(
			const T& yield,
			const bill::bill<T>& bill,
			price::price<T> price // to bring in market conventions
		) const -> price::price<T>;

	};


	template<typename T>
	auto ANBIMA<T>::price(
		const T& yield,
		const bill::bill<T>& bill,
		price::price<T> price
	) const -> price::price<T>
	{
		const auto cf = bill.cash_flow();
//		const auto dc = day_count::calcation_252{ cal };
//		const auto year_fraction = dc.fraction(price.get_settlement_date(), cf.get_date());

		return price; // mock up
	}

}
