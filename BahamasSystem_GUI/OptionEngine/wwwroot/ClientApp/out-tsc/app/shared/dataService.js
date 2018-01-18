var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
import { Subject } from 'rxjs/Subject';
import { Injectable } from "@angular/core";
import 'rxjs/add/operator/map';
let DataService = class DataService {
    constructor() {
        this.realisedPnL = 0;
        this.backtestDateIndex = 0;
        this.curPositions = [];
        this.positionsToCommit = new Map();
        //Subjects
        this.subject = new Subject();
        this.portfolioUpdateSubject = new Subject();
        this.backtestUpdateSubject = new Subject();
    }
    commitTrades() {
        this.subject.next({ text: 'commited' });
    }
    getMessage() {
        return this.subject.asObservable();
    }
    setPortfolioUpdate() {
        this.portfolioUpdateSubject.next({ text: 'metrics_updated' });
    }
    getPortfolioUpdate() {
        return this.portfolioUpdateSubject.asObservable();
    }
    getCurrentBacktestDate() {
        return this.backtestDateStream[this.backtestDateIndex];
    }
    setBacktestUpdate() {
        this.positionsToCommit = new Map();
        this.newPositionsValue = 0;
        this.setPortfolioUpdate();
        this.backtestUpdateSubject.next({ text: 'backtest_updated' });
    }
    getBacktestUpdate() {
        return this.backtestUpdateSubject.asObservable();
    }
};
DataService = __decorate([
    Injectable()
], DataService);
export { DataService };
//# sourceMappingURL=dataService.js.map