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

#include <resets_math.h>

#include <period.h>

#include <calendar.h>

#include <boost/multiprecision/cpp_dec_float.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono;
using namespace boost::multiprecision;
using namespace gregorian;
using namespace gregorian::util;
using namespace reset;


namespace debt_security // should we mock the ANBIMA calendar?
{

	TEST(ANBIMA, LTN1)
	{
		// from "Methodology for Calculating Federal Government Bonds Offered in Primary Auctions"

		const auto issue_date = 2007y / July / 1d; // made up (does not matter)
		const auto maturity_date = 2010y / July / 1d;
		const auto& calendar = make_calendar_ANBIMA();
		const auto face = 1000.0;
		const auto LTN = debt_security::bill{ issue_date, maturity_date, calendar, face };

		const auto settlement_date = 2008y / May / 21d;
		const auto truncate = 6u;
		const auto quote = debt_security::quote{ settlement_date, face, truncate };

		const auto ANBIMA = debt_security::ANBIMA{};

		// check the setup of the test first
		const auto bd = calendar.count_business_days(days_period{
			settlement_date,
			sys_days{ maturity_date } - days{ 1 } // "end date" should be excluded
		});
		EXPECT_EQ(bd, 532/*zu*/);

		const auto yield = from_percent(14.36);
		const auto price = ANBIMA.price(yield, LTN, quote);
		EXPECT_EQ(price, 753.315323);
	}

	TEST(ANBIMA, LTN2)
	{
		// from "Methodology for Calculating Federal Government Bonds Offered in Primary Auctions"

		const auto issue_date = 2007y / July / 1d; // made up (does not matter)
		const auto maturity_date = 2010y / July / 1d;
		const auto& calendar = make_calendar_ANBIMA();
		const auto face = cpp_dec_float_50{ 1000 };
		const auto LTN = debt_security::bill{ issue_date, maturity_date, calendar, face };

		const auto settlement_date = 2008y / May / 21d;
		const auto truncate = 6u;
		const auto quote = debt_security::quote{ settlement_date, face, truncate };

		const auto ANBIMA = debt_security::ANBIMA<cpp_dec_float_50>{};

		// check the setup of the test first
		const auto bd = calendar.count_business_days(days_period{
			settlement_date,
			sys_days{ maturity_date } - days{ 1 } // "end date" should be excluded
		});
		EXPECT_EQ(bd, 532/*zu*/);

		const auto yield = from_percent(cpp_dec_float_50{ "14.36" });
		const auto price = ANBIMA.price(yield, LTN, quote);
		EXPECT_EQ(price, cpp_dec_float_50{ "753.315323" });
	}


	TEST(ANBIMA, LFT1)
	{
		// from "Metodologia de Cálculo dos Títulos Públicos Federais Ofertados nos Leilões Primários"

		const auto issue_date = 2000y / July / 1d; // made up (does not matter)
		const auto maturity_date = 2014y / March / 7d;
		const auto& calendar = make_calendar_ANBIMA();
		const auto face = 100.0;
		const auto LFT = debt_security::bill{ issue_date, maturity_date, calendar, face };

		const auto settlement_date = 2008y / May / 21d;
		const auto truncate = 4u;
		const auto quote = debt_security::quote{ settlement_date, face, truncate };

		const auto ANBIMA = debt_security::ANBIMA{};

		// check the setup of the test first
		const auto bd = calendar.count_business_days(days_period{
			settlement_date,
			sys_days{ maturity_date } - days{ 1 } // "end date" should be excluded
		});
		EXPECT_EQ(bd, 1459/*zu*/);

		const auto yield = from_percent(-0.02);
		const auto price = ANBIMA.price(yield, LFT, quote);
		EXPECT_EQ(price, 100.1158);
	}

	TEST(ANBIMA, LFT2)
	{
		// from "Metodologia de Cálculo dos Títulos Públicos Federais Ofertados nos Leilões Primários"

		const auto issue_date = 2000y / July / 1d; // made up (does not matter)
		const auto maturity_date = 2014y / March / 7d;
		const auto& calendar = make_calendar_ANBIMA();
		const auto face = cpp_dec_float_50{ 100 };
		const auto LFT = debt_security::bill{ issue_date, maturity_date, calendar, face };

		const auto settlement_date = 2008y / May / 21d;
		const auto truncate = 4u;
		const auto quote = debt_security::quote{ settlement_date, face, truncate };

		const auto ANBIMA = debt_security::ANBIMA<cpp_dec_float_50>{};

		// check the setup of the test first
		const auto bd = calendar.count_business_days(days_period{
			settlement_date,
			sys_days{ maturity_date } - days{ 1 } // "end date" should be excluded
		});
		EXPECT_EQ(bd, 1459/*zu*/);

		const auto yield = from_percent(cpp_dec_float_50{ "-0.02" });
		const auto price = ANBIMA.price(yield, LFT, quote);
		EXPECT_EQ(price, cpp_dec_float_50{ "100.1158" });
	}

}
