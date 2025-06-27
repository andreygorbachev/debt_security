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

#include "calendar.h" // maybe not the best name as it clashes with gregorian

#include <ANBIMA.h>
#include <bill.h>
#include <quote.h>

#include <resets_math.h>

#include <calendar.h>

#include <boost/multiprecision/cpp_dec_float.hpp>

#include <chrono>
#include <iostream>
#include <limits>

using namespace std;
using namespace std::chrono;
using namespace boost::multiprecision;
using namespace gregorian;
using namespace gregorian::util;
using namespace reset;
using namespace debt_security;


constexpr auto start_date = 2025y / June / 26d;
constexpr auto number_of_bills = 365 * 50;
/*constexpr*/ const auto yield = cpp_dec_float_50{ 10 };


int main()
{
	const auto& calendar = make_calendar_ANBIMA();

	const auto settlement_date = start_date;
	const auto face = cpp_dec_float_50{ 1000 };
	const auto truncate = 6u;
	const auto q = quote<cpp_dec_float_50>{ settlement_date, face, truncate };

	const auto ym = ANBIMA<cpp_dec_float_50>{};

	const auto issue_date = start_date;
	for (auto i = 0; i < number_of_bills; ++i)
	{
		const auto maturity_date = year_month_day{ sys_days{ issue_date } + days{ i + 1 } };
		const auto b = bill<cpp_dec_float_50>{ issue_date, maturity_date, calendar, face };

		const auto y = from_percent(yield);
		const auto price = ym.price(y, b, q);

		cout
			<< setprecision(numeric_limits<cpp_dec_float_50>::max_digits10)
			<< "Issue date: " << issue_date
			<< ", Maturity date: " << maturity_date
			<< ", Yield: " << y
			<< ", Price: " << price
			<< endl;
	}
}
