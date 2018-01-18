var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};
import { Component } from '@angular/core';
import { DataService } from "../shared/dataService";
let MetricsSidebar = class MetricsSidebar {
    constructor(dataService) {
        this.dataService = dataService;
        this.currentNav = 0;
        this.newPositionsval = 0;
        this.unRealisedPnL = 0;
        this.realisedPnL = 0;
        this.currentDate = "2016-01-04T00:00:00";
        this.dataService.getPortfolioUpdate().subscribe(vals => {
            this.updatePortfolio();
        });
    }
    commitTradesBtn() {
        this.newPositionsval = 0;
        this.dataService.newPositionsValue = 0;
        this.dataService.commitTrades();
    }
    updatePortfolio() {
        this.currentNav = this.dataService.currentPortfolioValue;
        this.unRealisedPnL = this.dataService.unrealisedPnL;
        this.newPositionsval = this.dataService.newPositionsValue;
        this.realisedPnL = this.dataService.realisedPnL;
    }
    progressBacktestBtn() {
        this.dataService.backtestDateIndex++;
        this.dataService.setBacktestUpdate();
        this.currentDate = this.dataService.getCurrentBacktestDate();
    }
    revertBacktestBtn() {
        if (this.dataService.backtestDateIndex > 0) {
            this.dataService.backtestDateIndex--;
            this.dataService.setBacktestUpdate();
            this.currentDate = this.dataService.getCurrentBacktestDate();
        }
    }
};
MetricsSidebar = __decorate([
    Component({
        selector: "metrics_sidebar",
        templateUrl: "./metrics_sidebar.component.html",
        styles: []
    }),
    __metadata("design:paramtypes", [DataService])
], MetricsSidebar);
export { MetricsSidebar };
//# sourceMappingURL=metrics_sidebar.component.js.map