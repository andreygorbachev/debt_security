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

#include "setup.h"

#include <ANBIMA.h>
#include <bill.h>
#include <quote.h>

#include <calendar.h>
#include <period.h>

#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono;
using namespace gregorian;


namespace debt_security
{

	TEST(ANBIMA, price1)
	{
		// from "Methodology for Calculating Federal Government Bonds Offered in Primary Auctions"

		const auto issue_date = year_month_day{ 2007y / July / 1d }; // made up (does not matter)
		const auto maturity_date = year_month_day{ 2010y / July / 1d };
		const auto& cal = make_calendar_ANBIMA();
		const auto face = 1000.0;
		const auto LTN = bill{ issue_date, maturity_date, cal, face };

		const auto settlement_date = year_month_day{ 2008y / May / 21d };
		const auto quote = debt_security::quote{ settlement_date, face };

		const auto ANBIMA = debt_security::ANBIMA{};

		// check the setup of the test first
		const auto bd = cal.count_business_days(days_period{
			settlement_date,
			sys_days{ maturity_date } - days{ 1 } // "end date" should be expcuded
		});
		EXPECT_EQ(bd, 532);

		const auto yield = 0.1436;
		const auto price = ANBIMA.price(yield, LTN, quote);
		EXPECT_EQ(price, 753.315323);
	}

}
