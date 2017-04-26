#pragma once
#include<string>
#include<fstream>
#include<vector>

class AStarStrategyFactor
{
	struct Factor
	{
		double regionComparingFactor;
		double regionRankProportion;
		double foodMaxRank;
		double foodMinRank;
		double foodBaseRank;
		double foodRankDecreseProportion;
		int foodAmountCalculated;
		double foodRankProportion;
		double factorRank;
	};
public:
	AStarStrategyFactor(); 
	AStarStrategyFactor(
		double regionComparingFactor,
		double regionRankProportion,
		double foodMaxRank,
		double foodMinRank,
		double foodBaseRank,
		double foodRankDecreseProportion,
		int foodAmountCalculated,
		double foodRankProportion,
		double factorRank
		);
	~AStarStrategyFactor();
	void setFactorRank(double factorRank);
	void save()const;
	void load(); 
	double regionComparingFactor()const;
	double regionRankProportion()const;
	double foodMaxRank()const;
	double foodMinRank()const;
	double foodBaseRank()const;
	double foodRankDecreseProportion()const;
	int foodAmountCalculated()const;
	double foodRankProportion()const;
	double factorRank()const; 

private:
	std::string translate(const Factor& factor)const;
	Factor translate(const std::string& content)const;
	//get first 100 line content.if facotrs are insufficient,get all content (always ignore comments)
	std::vector<std::string> getFrontContent()const;
	Factor _factor; 
	const static std::string fileHead;
	const static std::string sourceFilePath;
	const static std::string tempFilePath;
};