import { Component, OnInit } from '@angular/core';
import { HttpClient } from "@angular/common/http";
import { Option } from "../shared/option";
import { DataService } from "../shared/dataService";
import { OptionPosition } from "../shared/optionposition";
import * as moment from 'moment';
declare var jquery: any;
declare var $: any;

@Component({
    selector: "matrix",
    templateUrl: "./matrix.component.html",
    styleUrls: ['matrix.component.css']
})
export class Matrix implements OnInit {
    constructor(private http: HttpClient, private dataService: DataService) {
        this.positionSelect.bind(this);

        //Subscribe to Commit Trade event
        this.dataService.getMessage().subscribe(msg => {
            this.commitTrades();
        });
        //Subscribe to backtest controls
        this.dataService.getBacktestUpdate().subscribe(msg => {
            this.updateMatrix();
        })
    }

    private matrix_Calls = new Map();
    private matrix_Puts = new Map();
    private dateIndex: number = 0;
    //private positionsToCommit = new Map();

    ngOnInit(): void {
        //Get available backtest dates
        this.http.get('home/getbacktestdates').subscribe(data => {
            this.dataService.backtestDateStream = data;
            this.updateMatrix();
        });

    }

    updateMatrix() {
        let backtestDate: string = this.dataService.getCurrentBacktestDate();
        this.http.get('home/getnewdata?id=' + backtestDate).subscribe(data => {
            this.parseData(data);
            this.updatePortfolioMetrics();
        });
    }

    parseData(data): void {
        this.matrix_Calls = new Map();
        this.matrix_Puts = new Map();

        //Add Headers to the matrix
        var headerElem = $('#matrixHeaders')[0];
        headerElem.innerHTML = "";
        var strikeHdr = document.createElement('th');
        strikeHdr.innerHTML = "Strike";
        headerElem.appendChild(strikeHdr);

        let dateKeys = Object.keys(data);
        var optionTables = $('.optionTable_Call');
        for (var _i = 0; _i < optionTables.length; _i++) {
            //Add Date Headers
            let a: moment.Moment = moment(this.dataService.getCurrentBacktestDate(), "YYYY/MM/DD hh:mm:ss");
            let b: moment.Moment = moment(dateKeys[_i]);
            var diffDays = b.diff(a, 'days');
            var dateHeader = document.createElement('th');
            dateHeader.innerHTML = dateKeys[_i] + " (DTE " + diffDays + ")";
            headerElem.appendChild(dateHeader);           
        }
        this.fillOptionTables('Call', dateKeys, data);
        this.fillOptionTables('Put', dateKeys, data);
    }

    fillOptionTables(selectorPrefix: string, dateKeys, data): void {

        var strikeTbl = $('#tableStrike_' + selectorPrefix)[0];
        strikeTbl.innerHTML = "";
        var strikeTbl_tHead = document.createElement('thead');
        var strikeTbl_tR = document.createElement('tr');
        var strikeTbl_hRow = document.createElement('th');
        strikeTbl_hRow.innerHTML = selectorPrefix;
        strikeTbl_hRow.scope = "col";
        strikeTbl_tR.appendChild(strikeTbl_hRow);
        strikeTbl_tHead.appendChild(strikeTbl_tR);
        strikeTbl.appendChild(strikeTbl_tHead);
        var strikeTbl_tBody = document.createElement('tbody');
        strikeTbl.appendChild(strikeTbl_tBody);

        let targetType: number;
        var optionTables = $('.optionTable_' + selectorPrefix);
        for (var _i = 0; _i < optionTables.length; _i++) {
            var curDateKey = dateKeys[_i];

            if (selectorPrefix == 'Call') {
                this.matrix_Calls.set(curDateKey, []);
                targetType = 0;
            }
            else if (selectorPrefix == 'Put') {
                this.matrix_Puts.set(curDateKey, []);
                targetType = 1;
            }

            //Add Option Table Column headers
            optionTables[_i].innerHTML = "<thead><tr><th scope=\"row\">Delta</th><th scope=\"row\">Market Price</th><th scope=\"row\">New Pos</th><th scope=\"row\">Ext. Pos</th> </tr></thead>";
            var optionTableBody = document.createElement('tbody');
            optionTables[_i].appendChild(optionTableBody);

            let opData = data[curDateKey];
            for (var j = 0; j < opData.length; j++) {
                if (opData[j]['optionType'] == targetType) {
                    if (selectorPrefix == 'Call')
                        this.matrix_Calls.get(curDateKey).push(opData[j]);
                    else if (selectorPrefix == 'Put')
                        this.matrix_Puts.get(curDateKey).push(opData[j]);

                    //Fill Strikes table
                    if (_i == 0) {
                        var strikeRow_Container = document.createElement('tr');
                        var strikeRow = document.createElement('th');
                        strikeRow.innerHTML = opData[j]["strikePrice"];
                        strikeRow.scope = "row";
                        strikeRow_Container.appendChild(strikeRow);

                        strikeTbl_tBody.appendChild(strikeRow_Container);
                    }

                    var optionRow = document.createElement('tr');
                    optionRow.id = opData[j]["strikePrice"] + ";" + opData[j]["expirationDate"] + ";" + selectorPrefix;

                    var opDelta = document.createElement('td');
                    opDelta.scope = "row";
                    opDelta.innerHTML = opData[j]["delta"];
                    optionRow.appendChild(opDelta);

                    var mktPrice = document.createElement('td');
                    mktPrice.innerHTML = opData[j]["marketPrice"];
                    optionRow.appendChild(mktPrice);

                    var newPos = document.createElement('td');
                    newPos.contentEditable = "true";
                    newPos.innerHTML = '';
                    newPos.oninput = (e) => { this.positionSelect(e, selectorPrefix); };
                    newPos.onblur = (e) => { this.positionDeSelect(e); };
                    optionRow.appendChild(newPos);

                    var extPos = document.createElement('td');
                    extPos.innerHTML = '-';

                    //Update positions Array
                    for (var p = 0; p < this.dataService.curPositions.length; p++) {
                        if (this.dataService.curPositions[p].expDate == dateKeys[_i] &&
                            this.dataService.curPositions[p].strike == opData[j]["strikePrice"] &&
                            this.dataService.curPositions[p].optionType == selectorPrefix) {

                            this.dataService.curPositions[p].curPrice = opData[j]["marketPrice"];

                            extPos.innerHTML = this.dataService.curPositions[p].units;
                            optionRow.className += 'positionActive';
                        }
                    }

                    optionRow.appendChild(extPos);
                    optionTableBody.appendChild(optionRow);
                }
            }
        }
    }

    positionDeSelect(evnt): void {
        let val = evnt.target.innerHTML;  
        if (val != '') {
            var parentRow = $(evnt.target).parent();

            let posId = parentRow[0].id;
            let rowData = this.getRowMetaData(posId);
            let strike = parseInt(rowData[0]);
            let expDate = rowData[1];
            let opType = rowData[2];
            let rowIndex = parentRow[0].rowIndex - 1;
            let selectedPosPrice; 

            if (opType == 'Call')
                selectedPosPrice = this.matrix_Calls.get(expDate)[rowIndex]["marketPrice"];
            else if (opType == 'Put')
                selectedPosPrice = this.matrix_Puts.get(expDate)[rowIndex]["marketPrice"];

            let tempPosition: OptionPosition = new OptionPosition;
            tempPosition.strike = strike;
            tempPosition.entryPrice = selectedPosPrice;
            tempPosition.units = val;
            tempPosition.optionType = opType;

            this.dataService.positionsToCommit.set(posId, tempPosition);
            this.dataService.setPortfolioUpdate();

            if (!parentRow.hasClass('posToAdd')) {
                parentRow.addClass('posToAdd');
            }
        }
    }

    positionSelect(evnt, selectorPrefix): void {
        var parentRow = $(evnt.target).parent();
        
        let posId = parentRow[0].id;
        let rowData = this.getRowMetaData(posId);
        let strike = rowData[0];
        let expDate = rowData[1];
        let rowIndex = parentRow[0].rowIndex - 1;
        let posValTot = 0;

        if (evnt.target.innerHTML == '') {
            parentRow.removeClass('posToAdd');
            this.dataService.positionsToCommit.get(posId)['entryPrice'] = 0;
            window.console.log(this.dataService.positionsToCommit);
        } else {
            let mktPrice;
            if (selectorPrefix == 'Call')
                mktPrice = this.matrix_Calls.get(expDate)[rowIndex]["marketPrice"];
            else if (selectorPrefix == 'Put')
                mktPrice = this.matrix_Puts.get(expDate)[rowIndex]["marketPrice"];

            posValTot = mktPrice * evnt.target.innerHTML * 100;
        }

        for (var [key, value] of this.dataService.positionsToCommit) {
            posValTot += (value['entryPrice'] * value['units'] * 100);
        }

        this.dataService.newPositionsValue = posValTot;
        this.dataService.setPortfolioUpdate();
    }

    commitTrades(): void {
        this.dataService.positionsToCommit = new Map();
        let newPositions = $('.posToAdd');

        //Convert new positions to trades
        for (let newPosition of newPositions) {
            let posId = newPosition.id;
            let rowData = this.getRowMetaData(posId);
            let strike = rowData[0];
            let expDate = rowData[1];
            let optionType = rowData[2];

            let rowIndex = $(newPosition)[0].rowIndex - 1;
            let newPositionUnits = 0;
            let newUnits = parseInt($(newPosition).children()[2].innerHTML)

            if ($(newPosition).hasClass('positionActive')) {
                //Position already exists, close if units = 0
                var posIndex = this.getPositionIndex(expDate, strike, optionType);
                newPositionUnits = newUnits + this.dataService.curPositions[posIndex].units;

                if (newPositionUnits == 0) {
                    //Close Position
                    let realisedPnL = (this.dataService.curPositions[posIndex].curPrice - this.dataService.curPositions[posIndex].entryPrice) * this.dataService.curPositions[posIndex].units * 100;
                    this.dataService.realisedPnL += realisedPnL;
                    this.dataService.curPositions.splice(posIndex, 1);
                } else {
                    this.dataService.curPositions[posIndex].units = newPositionUnits;
                }
            } else {
                //Add new position to existing positions array 
                let tempPosition: OptionPosition = new OptionPosition;

                if (optionType == "Call") {
                    tempPosition.curPrice = this.matrix_Calls.get(expDate)[rowIndex]["marketPrice"];
                    tempPosition.entryPrice = this.matrix_Calls.get(expDate)[rowIndex]["marketPrice"];
                } else if (optionType == "Put") {
                    tempPosition.curPrice = this.matrix_Puts.get(expDate)[rowIndex]["marketPrice"];
                    tempPosition.entryPrice = this.matrix_Puts.get(expDate)[rowIndex]["marketPrice"];
                }

                tempPosition.units = newUnits;
                tempPosition.optionType = optionType;
                tempPosition.strike = parseInt(strike);
                tempPosition.expDate = expDate;
                //tempPosition.entryDate = 

                newPositionUnits = tempPosition.units;
                this.dataService.curPositions.push(tempPosition);
                $(newPosition).addClass('positionActive');
            }

            //Set the value of the Existing position column
            $(newPosition).children()[3].innerHTML = newPositionUnits;
            $(newPosition).children()[2].innerHTML = '';

            //No Outstanding position on Option
            if (newPositionUnits == 0) {
                $(newPosition).children()[3].innerHTML = '-';
                $(newPosition).removeClass('positionActive');
            }

            this.updatePortfolioMetrics();
            $(newPosition).removeClass('posToAdd');
        }
    }

    updatePortfolioMetrics(): void {
        let portfolioTotal = 0;
        let unrealisedPnL = 0;

        //Calculate current portfolio NAV and PnL
        for (var i = 0; i < this.dataService.curPositions.length; i++) {
            portfolioTotal += (this.dataService.curPositions[i].curPrice) * this.dataService.curPositions[i].units;
            unrealisedPnL += (this.dataService.curPositions[i].curPrice - this.dataService.curPositions[i].entryPrice) * this.dataService.curPositions[i].units;
        }

        this.dataService.currentPortfolioValue = portfolioTotal * 100;
        this.dataService.unrealisedPnL = unrealisedPnL * 100;
        this.dataService.setPortfolioUpdate();
    }

    getRowMetaData(row): string[] {
        let metaData: string[] = row.split(";",3);
        return metaData;
    }

    getPositionIndex(targetDate, strike, type) {
        for (var i = 0; i < this.dataService.curPositions.length; i++) {
            if (this.dataService.curPositions[i].expDate == targetDate &&
                this.dataService.curPositions[i].strike == strike && 
                this.dataService.curPositions[i].optionType == type)
                return i;
        }
        return 0;
    }

    callTableScroll():void {
        let scrollVal = document.getElementById("callContainer_Options02").scrollTop;
        document.getElementById("callContainer_Options00").scrollTop = scrollVal;
        document.getElementById("callContainer_Options01").scrollTop = scrollVal;
        document.getElementById("callContainer_Strikes").scrollTop = scrollVal;
    }

    putTableScroll(): void {
        let scrollVal = document.getElementById("putContainer_Options02").scrollTop;
        document.getElementById("putContainer_Options00").scrollTop = scrollVal;
        document.getElementById("putContainer_Options01").scrollTop = scrollVal;
        document.getElementById("putContainer_Strikes").scrollTop = scrollVal;
    }
}