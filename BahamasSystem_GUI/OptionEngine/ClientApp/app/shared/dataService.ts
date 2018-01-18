import { Observable } from "rxjs";
import { Subject } from 'rxjs/Subject';
import { Injectable } from "@angular/core";
import 'rxjs/add/operator/map';

@Injectable()
export class DataService {

    public unrealisedPnL: number;
    public realisedPnL: number = 0;
    public newPositionsValue: number;
    public currentPortfolioValue: number;
    public backtestDateIndex: number = 0;
    public backtestDateStream: any;
    public curPositions = [];
    public positionsToCommit = new Map();

    //Subjects
    private subject = new Subject<any>();
    private portfolioUpdateSubject = new Subject<any>();
    private backtestUpdateSubject = new Subject<any>();
    
    commitTrades() {
        this.subject.next({ text: 'commited' }); 
    }
    getMessage(): Observable<any> {
        return this.subject.asObservable();
    }

    setPortfolioUpdate() {
        this.portfolioUpdateSubject.next({ text: 'metrics_updated' });
    }
    getPortfolioUpdate() {
        return this.portfolioUpdateSubject.asObservable();
    }

    getCurrentBacktestDate(): string {
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
}