﻿import { Component, OnInit } from '@angular/core';
import { DataService } from "../shared/dataService";
declare var Plotly: any;
declare var jquery: any;
declare var $: any;

@Component({
    selector: "profile",
    templateUrl: "./profile.component.html",
    styleUrls: []
})
export class Profile implements OnInit {

    private chartLayout = {
        autosize: false,
        width: 700,
        height: 700,
        margin: {
            l: 50,
            r: 50,
            b: 100,
            t: 50,
            pad: 4
        }
    };
    private chartContainer;
    private underlyingStrikes: number[] = [];

    constructor(private dataService: DataService) {
        this.dataService.getPortfolioUpdate().subscribe(vals => {
            this.updateProfile();
        });
        for (var _i = 900; _i < 1300; _i += 10) {
            this.underlyingStrikes.push(_i);
        }
    }  

    ngOnInit(): void {
        var posData = {
            x: [],
            y: [],
            type: 'scatter'
        };
        var data = [posData];
        this.chartContainer = $('#chart')[0];
        Plotly.newPlot(this.chartContainer, data, this.chartLayout);
    }

    updateProfile(): void {
        let yVals = [];
        let tPlusXVals = [];
        for (var _i = 0; _i < this.underlyingStrikes.length; _i += 1) {
            let positionTotal = 0;
            let tPlusTot = 0;
            for (var [key, value] of this.dataService.positionsToCommit) {
                var optionStrike = value["strike"];
                var mktPrice = value["entryPrice"];
                var units = parseInt(value["units"]);
                positionTotal += (Math.max(0, optionStrike - this.underlyingStrikes[_i]) - mktPrice) * units;
                tPlusTot += (this.BlackScholes("put", this.underlyingStrikes[_i], optionStrike, 0.1, 0.01, 0.3) - mktPrice) * units;                
            }
            for (var optionPos of this.dataService.curPositions) {
                var optionStrike = optionPos["strike"];
                var mktPrice = optionPos["entryPrice"];
                var units = parseInt(optionPos["units"]);
                positionTotal += (Math.max(0, optionStrike - this.underlyingStrikes[_i]) - mktPrice) * units;
                tPlusTot += (this.BlackScholes("put", this.underlyingStrikes[_i], optionStrike, 0.1, 0.01, 0.3) - mktPrice) * units;  
            }
            yVals.push(positionTotal * 100);
            tPlusXVals.push(tPlusTot * 100);
        }
        var posData = {
            x: this.underlyingStrikes,
            y: yVals,
            type: 'scatter'
        };
        var tPlusX = {
            x: this.underlyingStrikes,
            y: tPlusXVals,
            type: 'scatter'
        }
        var data = [posData, tPlusX];
        Plotly.newPlot(this.chartContainer, data, this.chartLayout);
    }

    CND(x) {
        if (x < 0) {
            return (1 - this.CND(-x));
        } else {
            let k = 1 / (1 + .2316419 * x);
            return (1 - Math.exp(-x * x / 2) / Math.sqrt(2 * Math.PI) * k * (.31938153 + k * (-.356563782 + k * (1.781477937 + k * (-1.821255978 + k * 1.330274429)))));
        }
    }

    BlackScholes(PutCallFlag, S, X, T, r, v) {
        let d1 = (Math.log(S / X) + (r + v * v / 2) * T) / (v * Math.sqrt(T));
        let d2 = d1 - v * Math.sqrt(T);

        if (PutCallFlag === "call") {
            return (S * this.CND(d1) - X * Math.exp(-r * T) * this.CND(d2));
        } else {
            return (X * Math.exp(-r * T) * this.CND(-d2) - S * this.CND(-d1));
        }
    }
}