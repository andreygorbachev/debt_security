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

#include <chrono>
#include <iostream>
#include <iomanip>
#include <limits>

#include <boost/decimal.hpp>

#include <reset_math.h>

#include <static_data.h>

#include <ANBIMA.h>
#include <bill.h>
#include <quote.h>

using namespace std;
using namespace std::chrono;
using namespace boost::decimal;
using namespace boost::decimal::literals;
using namespace gregorian;
using namespace gregorian::static_data;
using namespace reset;
using namespace debt_security;


constexpr auto min_yield = 5.0000_dl;
constexpr auto max_yield = 15.0000_dl;
constexpr auto yield_step = 0.0001_dl;


int main()
{
	const auto& calendar = locate_calendar("America/ANBIMA", 2008y / May / 21d);

	constexpr auto issue_date = 2008y / May / 21d;
	constexpr auto maturity_date = 2010y / July / 1d;
	constexpr auto face = 1'000_dl;
	const auto b_dec = bill{ issue_date, maturity_date, calendar, face };
	const auto b_bin = bill{ issue_date, maturity_date, calendar, static_cast<double>(face) };

	const auto settlement_date = issue_date;
	const auto price_truncate = 6u;
	const auto q_dec = quote{ settlement_date, face, price_truncate };
	const auto q_bin = quote{ settlement_date, static_cast<double>(face), price_truncate };

	const auto ym_dec = debt_security::ANBIMA<decimal128_t>{};
	const auto ym_bin = debt_security::ANBIMA<double>{};

	auto diff = 0_dl;
	for (auto yield = min_yield; yield <= max_yield; yield += yield_step)
	{
		const auto yield_truncate = 4u;

		const auto y_dec = from_percent(trunc_dp(yield, yield_truncate));
		const auto p_dec = ym_dec.price(y_dec, b_dec, q_dec);

		const auto y_bin = from_percent(trunc_dp(static_cast<double>(yield), yield_truncate));
		const auto p_bin = ym_bin.price(y_bin, b_bin, q_bin);

		const auto new_diff = abs(p_dec - static_cast<decimal128_t>(p_bin));
		if (new_diff > diff)
		{
			diff = new_diff;

			cout
				<< setprecision(numeric_limits<double>::max_digits10)
				<< "New largest diff: " << diff << " for yield: " << yield
				<< ", Price (decimal): " << p_dec << ", Price (binary): " << p_bin << endl;
		}
	}
}
