#include<sstream>
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
ASSERT_GREAT_THAN((factor).foodAmountCalculated, 0, "food amout must greater than zero");\
ASSERT_GREAT_THAN((factor).foodBaseRank, 0, "food base rank must greater than zero");\
ASSERT_GREAT_THAN((factor).foodMaxRank, 0, "food max rank must greater than zero");\
ASSERT_GREAT_THAN((factor).foodMaxRank, (factor).foodMinRank, "food max rank must greater than food min rank");\
ASSERT_GREAT_THAN((factor).foodMinRank, 0, "food amout must greater than zero");\
ASSERT_GREAT_THAN((factor).foodRankDecreseProportion, 0, "food rank decrese proportion must greater than zero");\
ASSERT_LESS_THAN((factor).foodRankDecreseProportion, 1, "ood rank decrese proportion  must less than one");\
ASSERT_GREAT_THAN((factor).foodRankProportion, 0, "food rank proportion must greater than zero");\
ASSERT_GREAT_THAN((factor).regionComparingFactory, 0, "region comparing must greater than zero");\
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
	const double regionComparingFactory,
	const double regionRankProportion,
	const double foodMaxRank,
	const double foodMinRank,
	const double foodBaseRank,
	const double foodRankDecreseProportion,
	const int foodAmountCalculated,
	const double foodRankProportion,
	const double factorRank):
	_factor{
	regionComparingFactory,
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
	bool thisInserted{};
	int index = 0;
	for (auto& i : getFrontContent())
	{
		auto factor = translate(i);
		if (!thisInserted&&factor.factorRank < _factor.factorRank)
		{
			fout << ++index << "    " << translate(factor) << '\n';
			thisInserted = true;
		}
		fout << ++index << "    " << i << '\n';
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
		ansFactor.regionComparingFactory += tempFactor.regionComparingFactory;
		ansFactor.regionRankProportion += tempFactor.regionRankProportion;
	}
	const int size = content.size();
	ansFactor.foodBaseRank /= size;
	ansFactor.foodMaxRank /= size;
	ansFactor.foodMinRank /= size;
	ansFactor.foodRankDecreseProportion /= size;
	ansFactor.foodRankProportion /= size;
	ansFactor.regionComparingFactory /= size;
	ansFactor.regionRankProportion /= size;
	_factor = ansFactor;
	ASSERT_FACTOR_LEGAL(_factor);
}

std::string && AStarStrategyFactor::translate(const Factor & factor) const
{
	static std::string interval("    ");
	static std::stringstream ss;
	ss.str();//clear buffer
	ss << factor.regionComparingFactory << interval << factor.regionRankProportion << interval << factor.foodMaxRank << interval
		<< factor.foodMinRank << interval << factor.foodBaseRank << interval << factor.foodRankDecreseProportion << interval
		<< factor.foodAmountCalculated << interval << factor.foodRankProportion << interval << factor.factorRank;
	return std::move(ss.str());
}

AStarStrategyFactor::Factor AStarStrategyFactor::translate(const std::string & content) const
{
	static std::stringstream ss;
	ss.str(content);
	int index;//never used
	Factor factor;
	ss >> index >> factor.regionComparingFactory >> factor.regionRankProportion >> factor.foodMaxRank
		>> factor.foodMinRank >> factor.foodBaseRank >> factor.foodRankDecreseProportion >> factor.foodAmountCalculated
		>> factor.foodRankProportion >> factor.factorRank;
	ASSERT_FACTOR_LEGAL(factor);
	return factor;
}

std::vector<std::string>&& AStarStrategyFactor::getFrontContent() const
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
	auto factorVecotr = new std::vector<std::string>();
	factorVecotr->reserve(static_cast<size_t>(amoutLimit));
	while (std::getline(fin, content) && ++amountGot <= amoutLimit)
	{// read content
		factorVecotr->emplace_back(std::move(content));
	}
	fin.close();
	return std::move(*factorVecotr);
}
