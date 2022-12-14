// Workshop 5: Counter trend trading, optimized ////////////////

function run()
{
	StartDate = 2005;
	EndDate = 2019; 	

	set(PLOTNOW);  // generate and use optimized parameters
	BarPeriod = 1440;	// 4 hour bars
	LookBack = 500;
	if(Train) Detrend = TRADES;
	NumWFOCycles = 10; // activate WFO

	if(ReTrain) {
		UpdateDays = -1;	// update price data from the server 
		SelectWFO = -1;	// select the last cycle for re-optimization
	}
	
// calculate the buy/sell signal
	vars Price = series(price());
	var BestCycle = optimize(30,25,35);
	vars Filtered = series(BandPass(Price,BestCycle,0.5));
	vars Signal = series(FisherN(Filtered,500));
	var Threshold = optimize(1,0.5,1.5,0.1);

// buy and sell
	Stop = optimize(4,2,10) * ATR(100);
	Trail = 4*ATR(100);

	var Cycle = DominantPeriod(Price,10);
	
	if(between(Cycle,BestCycle-10,BestCycle+10)) {
		if(crossUnder(Signal,-Threshold))
			reverseLong(1); 
		else if(crossOver(Signal,Threshold))
			reverseShort(1);
	}
	
	PlotWidth = 800;
	PlotHeight1 = 400;
	ColorWin = ColorLoss = 0;
	ColorUp = ColorDn = 0;
	ColorDD = 0x010101;
	ColorEquity = GREY;
	set(TESTNOW);
} 