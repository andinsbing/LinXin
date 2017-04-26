#include<sstream>
#include<type_traits>
#include<algorithm>
#include "AStarStrategyFactor.h"
#include"macro.h"

const std::string AStarStrategyFactor::fileHead{
"#=========================================================\n"
"#config for AStarStrategyFactor class in order of rank \n"
"#sequence | constuction factor in order | rank \n"
"#=========================================================\n"
};

const std::string AStarStrategyFactor::sourceFilePath{ "config.ini" };
const std::string AStarStrategyFactor::tempFilePath{ "temp.ini" };

#define ASSERT_FACTOR_LEGAL(factor)	{\
ASSERT_GREAT_THAN((factor).foodAmountCalculated, 0, "food amout calculated must greater than zero");\
ASSERT_GREAT_THAN((factor).foodBaseRank, 0, "food base rank must greater than zero");\
ASSERT_GREAT_THAN((factor).foodMaxRank, 0, "food max rank must greater than zero");\
ASSERT_GREAT_THAN((factor).foodMaxRank, (factor).foodMinRank, "food max rank must greater than food min rank");\
ASSERT_GREATEQU_THAN((factor).foodMinRank, 0, "food foodMinRank must greater than or equal to zero");\
ASSERT_GREAT_THAN((factor).foodRankDecreseProportion, 0, "food rank decrese proportion must greater than zero");\
ASSERT_LESS_THAN((factor).foodRankDecreseProportion, 1, "food rank decrese proportion  must less than one");\
ASSERT_GREAT_THAN((factor).foodRankProportion, 0, "food rank proportion must greater than zero");\
ASSERT_GREAT_THAN((factor).regionComparingFactor, 0, "region comparing must greater than zero");\
ASSERT_GREAT_THAN((factor).regionRankProportion, 0, "region rank proportion must greater than zero");\
}

AStarStrategyFactor::AStarStrategyFactor():
	AStarStrategyFactor(
		1.5,
		1,
		100000,
		0,
		10000,
		0.9,
		3,
		1,
		0)
{
} 

AStarStrategyFactor::AStarStrategyFactor(
	const double regionComparingFactor,
	const double regionRankProportion,
	const double foodMaxRank,
	const double foodMinRank,
	const double foodBaseRank,
	const double foodRankDecreseProportion,
	const int foodAmountCalculated,
	const double foodRankProportion,
	const double factorRank):
	_factor{
	regionComparingFactor,
	regionRankProportion,
	foodMaxRank,
	foodMinRank,
	foodBaseRank,
	foodRankDecreseProportion,
	foodAmountCalculated,
	foodRankProportion,
	factorRank
	}
{ 
	ASSERT_FACTOR_LEGAL(_factor);
}

AStarStrategyFactor::~AStarStrategyFactor()
{  

}

void AStarStrategyFactor::setFactorRank(double factorRank)
{
	_factor.factorRank = factorRank;
}

void AStarStrategyFactor::save()const
{ 
	ASSERT_NOT_EQUAL(_factor.factorRank, 0, "factor have not been initialized");
	std::ofstream fout(tempFilePath);
	ASSERT_TRUE(fout, (tempFilePath + "   opened failed").c_str());
	bool thisPrinted{};
	int index = 0;
	for (auto& i : getFrontContent())
	{
		auto factor = translate(i);
		if (!thisPrinted&&factor.factorRank < _factor.factorRank)
		{
			fout << ++index << "    " << translate(_factor) << '\n';
			thisPrinted = true;
		}
		fout << ++index << "    " << i << '\n';
	}
	if (!thisPrinted)
	{ 
		fout << ++index << "    " << translate(_factor) << '\n';
	}

	fout.close();
	std::ifstream fin(tempFilePath);
	fout.open(sourceFilePath);
	ASSERT_TRUE(fin, (tempFilePath + "   opened failed").c_str());
	ASSERT_TRUE(fout, (sourceFilePath + "   opened failed").c_str());
	fout << fileHead;
	std::string content;
	while (std::getline(fin, content))
	{// copy temp file to source file
		fout << content << '\n';
	}
	fin.close();
	fout.close();
}

void AStarStrategyFactor::load()
{
	Factor ansFactor{};
	auto content = getFrontContent();
	if (content.empty())
	{ //do nothing
		return;
	}
	// assume some factor
	ansFactor.factorRank = 0;
	ansFactor.foodAmountCalculated = 3;
	// choose average for other factor 
	for (auto &i : content)
	{
		auto tempFactor = translate(i);
		ansFactor.foodBaseRank += tempFactor.foodBaseRank;
		ansFactor.foodMaxRank += tempFactor.foodMaxRank;
		ansFactor.foodMinRank += tempFactor.foodMinRank;
		ansFactor.foodRankDecreseProportion += tempFactor.foodRankDecreseProportion;
		ansFactor.foodRankProportion += tempFactor.foodRankProportion;
		ansFactor.regionComparingFactor += tempFactor.regionComparingFactor;
		ansFactor.regionRankProportion += tempFactor.regionRankProportion;
	} 
	const double size = content.size();
	ansFactor.foodBaseRank = ansFactor.foodBaseRank / size *(static_cast<double>(rand() % 200 + 1) / 1000 + 0.8);
	ansFactor.foodMaxRank = ansFactor.foodMaxRank / size *(static_cast<double>(rand() % 200 + 1) / 1000 + 0.8);
	ansFactor.foodMinRank = ansFactor.foodMinRank / size *(static_cast<double>(rand() % 200 + 1) / 1000 + 0.8);
	ansFactor.foodRankDecreseProportion = ansFactor.foodRankDecreseProportion / size *(static_cast<double>(rand() % 200 + 1) / 1000 + 0.8);
	ansFactor.foodRankProportion = ansFactor.foodRankProportion / size *(static_cast<double>(rand() % 200 + 1) / 1000 + 0.8);
	ansFactor.regionComparingFactor = ansFactor.regionComparingFactor / size *(static_cast<double>(rand() % 200 + 1) / 1000 + 0.8);
	ansFactor.regionRankProportion = ansFactor.regionRankProportion / size *(static_cast<double>(rand() % 200 + 1) / 1000 + 0.8);
	
	ansFactor.foodMaxRank = std::min(ansFactor.foodMaxRank, 10000000.0);
	ansFactor.foodMaxRank = std::max(ansFactor.foodMaxRank, 10000.0);
	ansFactor.foodMinRank = std::min(ansFactor.foodMinRank, ansFactor.foodMaxRank / 1.5);
	ansFactor.foodMinRank = std::max(ansFactor.foodMinRank, 100.0);
	ansFactor.foodRankDecreseProportion = std::min(ansFactor.foodRankDecreseProportion, 0.99);
	ansFactor.foodRankDecreseProportion = std::max(ansFactor.foodRankDecreseProportion, 0.1);
	ansFactor.foodBaseRank = std::min(ansFactor.foodMaxRank, ansFactor.foodMaxRank/2);
	ansFactor.foodBaseRank = std::max(ansFactor.foodMaxRank, ansFactor.foodMaxRank / 10);

	_factor = ansFactor;
	ASSERT_FACTOR_LEGAL(_factor);
}

double AStarStrategyFactor::regionComparingFactor() const
{
	return _factor.regionComparingFactor;
}

double AStarStrategyFactor::regionRankProportion() const
{
	return _factor.regionRankProportion;
}

double AStarStrategyFactor::foodMaxRank() const
{
	return _factor.foodMaxRank;
}

double AStarStrategyFactor::foodMinRank() const
{
	return _factor.foodMinRank;
}

double AStarStrategyFactor::foodBaseRank() const
{
	return _factor.foodBaseRank;
}

double AStarStrategyFactor::foodRankDecreseProportion() const
{
	return _factor.foodRankDecreseProportion;
}

int AStarStrategyFactor::foodAmountCalculated() const
{
	return _factor.foodAmountCalculated;
}

double AStarStrategyFactor::foodRankProportion() const
{
	return _factor.foodRankProportion;
}

double AStarStrategyFactor::factorRank() const
{
	return _factor.factorRank;
}

std::string AStarStrategyFactor::translate(const Factor & factor) const
{
	static std::string interval("    ");
	static std::stringstream ss;
	ss.str("");//clear buffer
	ss << factor.regionComparingFactor << interval << factor.regionRankProportion << interval << factor.foodMaxRank << interval
		<< factor.foodMinRank << interval << factor.foodBaseRank << interval << factor.foodRankDecreseProportion << interval
		<< factor.foodAmountCalculated << interval << factor.foodRankProportion << interval << factor.factorRank;
	return std::move(ss.str());
}

AStarStrategyFactor::Factor AStarStrategyFactor::translate(const std::string & content) const
{
	static std::stringstream ss;
	ss.clear();
	ss.str(content);
	Factor factor;
	ss >> factor.regionComparingFactor >> factor.regionRankProportion >> factor.foodMaxRank
		>> factor.foodMinRank >> factor.foodBaseRank >> factor.foodRankDecreseProportion >> factor.foodAmountCalculated
		>> factor.foodRankProportion >> factor.factorRank;
	ASSERT_FACTOR_LEGAL(factor);
	return factor;
}

std::vector<std::string> AStarStrategyFactor::getFrontContent() const
{ 
	static const int amoutLimit = 100;//max amount of content to read
	static const char commentsSymbol{ '#' };
	std::ifstream fin(sourceFilePath);
	ASSERT_TRUE(fin, (sourceFilePath + "   opened failed").c_str());
	while (fin.peek() == commentsSymbol)
	{// ignore head comments
		fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::string content;
	int amountGot = 0;
	std::vector<std::string> factorVecotr;
	factorVecotr.reserve(static_cast<size_t>(amoutLimit)); 
	while (std::getline(fin, content) && ++amountGot <= amoutLimit)
	{// read content 
		auto it = content.begin();
		while (isdigit(*it++));
		while (isblank(*it++));
		content.erase(content.begin(), --it);
		factorVecotr.emplace_back(std::move(content));
	}
	fin.close();
	return std::move(factorVecotr);
}
