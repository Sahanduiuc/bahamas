import { Component } from '@angular/core';
import { DataService } from "../shared/dataService";

@Component({
    selector: "metrics_sidebar",
    templateUrl: "./metrics_sidebar.component.html",
    styles: []
})
export class MetricsSidebar {
    private currentNav: number = 0;
    private newPositionsval: number = 0;
    private unRealisedPnL: number = 0;
    private realisedPnL: number = 0;
    private currentDate: string = "2016-01-04T00:00:00";

    constructor(private dataService: DataService) {
        this.dataService.getPortfolioUpdate().subscribe(vals => {
            this.updatePortfolio();
        });
    }

    commitTradesBtn(): void {
        this.newPositionsval = 0;
        this.dataService.newPositionsValue = 0;
        this.dataService.commitTrades();
    }

    updatePortfolio(): void {
        this.currentNav = this.dataService.currentPortfolioValue;
        this.unRealisedPnL = this.dataService.unrealisedPnL;
        this.newPositionsval = this.dataService.newPositionsValue;
        this.realisedPnL = this.dataService.realisedPnL;
    }

    progressBacktestBtn(): void {
        this.dataService.backtestDateIndex++;
        this.dataService.setBacktestUpdate();
        this.currentDate = this.dataService.getCurrentBacktestDate();
    }
    revertBacktestBtn(): void {
        if (this.dataService.backtestDateIndex > 0) {
            this.dataService.backtestDateIndex--;
            this.dataService.setBacktestUpdate();
            this.currentDate = this.dataService.getCurrentBacktestDate();
        }
    }
}