webpackJsonp(["main"],{

/***/ "../../../../../ClientApp/$$_lazy_route_resource lazy recursive":
/***/ (function(module, exports) {

function webpackEmptyAsyncContext(req) {
	// Here Promise.resolve().then() is used instead of new Promise() to prevent
	// uncatched exception popping up in devtools
	return Promise.resolve().then(function() {
		throw new Error("Cannot find module '" + req + "'.");
	});
}
webpackEmptyAsyncContext.keys = function() { return []; };
webpackEmptyAsyncContext.resolve = webpackEmptyAsyncContext;
module.exports = webpackEmptyAsyncContext;
webpackEmptyAsyncContext.id = "../../../../../ClientApp/$$_lazy_route_resource lazy recursive";

/***/ }),

/***/ "../../../../../ClientApp/app/app.component.html":
/***/ (function(module, exports) {

module.exports = "<div class=\"row\" style=\"height:710px\">\r\n    <div class=\"col-lg-1\">\r\n        <ul class=\"nav nav-pills nav-stacked\" role=\"tablist\">\r\n            <li class=\"active\"><a href=\"#\">Matrix</a></li>\r\n            <li><a href=\"#\">Profile</a></li>\r\n        </ul>\r\n    </div>\r\n    <div class=\"col-lg-9\">\r\n        <code_editor></code_editor>\r\n    </div>\r\n</div>\r\n<div class=\"row\">\r\n    <div class=\"col-lg-9\">\r\n        <matrix></matrix>\r\n    </div>\r\n    <div class=\"col-md-offset-10 well\">\r\n        <metrics_sidebar></metrics_sidebar>\r\n    </div>\r\n</div>\r\n<!--<profile></profile>-->\r\n\r\n"

/***/ }),

/***/ "../../../../../ClientApp/app/app.component.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return AppComponent; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};

let AppComponent = class AppComponent {
    constructor() {
        this.title = 'The App Title';
    }
};
AppComponent = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["m" /* Component */])({
        selector: 'dashboard',
        template: __webpack_require__("../../../../../ClientApp/app/app.component.html"),
        styles: []
    })
], AppComponent);



/***/ }),

/***/ "../../../../../ClientApp/app/app.module.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return AppModule; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_platform_browser__ = __webpack_require__("../../../platform-browser/esm2015/platform-browser.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__angular_common_http__ = __webpack_require__("../../../common/esm2015/http.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__app_component__ = __webpack_require__("../../../../../ClientApp/app/app.component.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4__shop_productList_component__ = __webpack_require__("../../../../../ClientApp/app/shop/productList.component.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_5__shared_dataService__ = __webpack_require__("../../../../../ClientApp/app/shared/dataService.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_6__metrics_sidebar_metrics_sidebar_component__ = __webpack_require__("../../../../../ClientApp/app/metrics_sidebar/metrics_sidebar.component.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_7__matrix_matrix_component__ = __webpack_require__("../../../../../ClientApp/app/matrix/matrix.component.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_8__profile_profile_component__ = __webpack_require__("../../../../../ClientApp/app/profile/profile.component.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_9__code_editor_code_editor_component__ = __webpack_require__("../../../../../ClientApp/app/code_editor/code_editor.component.ts");
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};










let AppModule = class AppModule {
};
AppModule = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_1__angular_core__["E" /* NgModule */])({
        declarations: [
            __WEBPACK_IMPORTED_MODULE_3__app_component__["a" /* AppComponent */],
            __WEBPACK_IMPORTED_MODULE_4__shop_productList_component__["a" /* ProductList */],
            __WEBPACK_IMPORTED_MODULE_6__metrics_sidebar_metrics_sidebar_component__["a" /* MetricsSidebar */],
            __WEBPACK_IMPORTED_MODULE_7__matrix_matrix_component__["a" /* Matrix */],
            __WEBPACK_IMPORTED_MODULE_8__profile_profile_component__["a" /* Profile */],
            __WEBPACK_IMPORTED_MODULE_9__code_editor_code_editor_component__["a" /* CodeEditor */]
        ],
        imports: [
            __WEBPACK_IMPORTED_MODULE_0__angular_platform_browser__["a" /* BrowserModule */],
            __WEBPACK_IMPORTED_MODULE_2__angular_common_http__["b" /* HttpClientModule */]
        ],
        providers: [
            __WEBPACK_IMPORTED_MODULE_5__shared_dataService__["a" /* DataService */]
        ],
        bootstrap: [__WEBPACK_IMPORTED_MODULE_3__app_component__["a" /* AppComponent */]]
    })
], AppModule);



/***/ }),

/***/ "../../../../../ClientApp/app/code_editor/code_editor.component.css":
/***/ (function(module, exports, __webpack_require__) {

exports = module.exports = __webpack_require__("../../../../css-loader/lib/css-base.js")(false);
// imports


// module
exports.push([module.i, "#editor {\n    position: absolute;\n    top: 0;\n    right: 0;\n    bottom: 0;\n    left: 0px;\n    height: 700px;\n    font-size: 14px;\n}\n", ""]);

// exports


/*** EXPORTS FROM exports-loader ***/
module.exports = module.exports.toString();

/***/ }),

/***/ "../../../../../ClientApp/app/code_editor/code_editor.component.html":
/***/ (function(module, exports) {

module.exports = "<div id=\"editor\">\r\n    \r\n</div>\r\n"

/***/ }),

/***/ "../../../../../ClientApp/app/code_editor/code_editor.component.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return CodeEditor; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};

let CodeEditor = class CodeEditor {
    constructor() {
        this.codeSample = `
    static int Main(string[] args) {
        return 0;
    }
`;
    }
    ngOnInit() {
        var editor = ace.edit("editor");
        editor.setTheme("ace/theme/monokai");
        editor.getSession().setMode("ace/mode/csharp");
        editor.setValue(this.codeSample);
    }
};
CodeEditor = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["m" /* Component */])({
        selector: "code_editor",
        template: __webpack_require__("../../../../../ClientApp/app/code_editor/code_editor.component.html"),
        styles: [__webpack_require__("../../../../../ClientApp/app/code_editor/code_editor.component.css")]
    }),
    __metadata("design:paramtypes", [])
], CodeEditor);



/***/ }),

/***/ "../../../../../ClientApp/app/matrix/matrix.component.css":
/***/ (function(module, exports, __webpack_require__) {

exports = module.exports = __webpack_require__("../../../../css-loader/lib/css-base.js")(false);
// imports


// module
exports.push([module.i, ":host ::ng-deep .posToAdd {\r\n    background-color: greenyellow;\r\n}\r\n\r\n:host ::ng-deep .positionActive {\r\n    background-color: hotpink;\r\n}\r\n\r\nth:hover {\r\n    background-color: cornsilk;\r\n}\r\n", ""]);

// exports


/*** EXPORTS FROM exports-loader ***/
module.exports = module.exports.toString();

/***/ }),

/***/ "../../../../../ClientApp/app/matrix/matrix.component.html":
/***/ (function(module, exports) {

module.exports = "<div id=\"matrix\">\r\n    <table class=\"table table-bordered\">\r\n        <thead>\r\n            <tr id=\"matrixHeaders\"></tr>\r\n        </thead>\r\n        <tbody>\r\n            <tr>\r\n                <th scope=\"row\">\r\n                    <div id=\"callContainer_Strikes\" style=\"height:100px; width:80px; overflow:auto;\">\r\n                        <table id=\"tableStrike_Call\" class=\"table\"></table>\r\n                    </div>\r\n                </th>\r\n                <th scope=\"row\">\r\n                    <div id=\"callContainer_Options00\" style=\"height:100px; overflow:auto;\">\r\n                        <table id=\"callTable00\" class=\"table optionTable_Call\"></table>\r\n                    </div>\r\n                </th>\r\n                <th scope=\"row\">\r\n                    <div id=\"callContainer_Options01\" style=\"height:100px; overflow:auto;\">\r\n                        <table id=\"callTable01\" class=\"table optionTable_Call\"></table>\r\n                    </div>\r\n                </th>\r\n                <th scope=\"row\">\r\n                    <div id=\"callContainer_Options02\" style=\"height:100px; overflow:auto;\" (scroll)=\"callTableScroll()\">\r\n                        <table id=\"callTable02\" class=\"table optionTable_Call\"></table>\r\n                    </div>\r\n                </th>\r\n            </tr>\r\n            <tr>\r\n                <th scope=\"row\">\r\n                    <div id=\"putContainer_Strikes\" style=\"height:500px; width:80px; overflow:auto;\">\r\n                        <table id=\"tableStrike_Put\" class=\"table\"></table>\r\n                    </div>\r\n                </th>\r\n                <th scope=\"row\">\r\n                    <div id=\"putContainer_Options00\" style=\"height:500px; overflow:auto;\">\r\n                        <table id=\"callTable00\" class=\"table optionTable_Put\"></table>\r\n                    </div>\r\n                </th>\r\n                <th scope=\"row\">\r\n                    <div id=\"putContainer_Options01\" style=\"height:500px; overflow:auto;\">\r\n                        <table id=\"putTable01\" class=\"table optionTable_Put\"></table>\r\n                    </div>\r\n                </th>\r\n                <th scope=\"row\">\r\n                    <div id=\"putContainer_Options02\" style=\"height:500px; overflow:auto;\" (scroll)=\"putTableScroll()\">\r\n                        <table id=\"putTable02\" class=\"table optionTable_Put\"></table>\r\n                    </div>\r\n                </th>\r\n            </tr>\r\n        </tbody>\r\n    </table>\r\n</div>\r\n\r\n"

/***/ }),

/***/ "../../../../../ClientApp/app/matrix/matrix.component.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return Matrix; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_common_http__ = __webpack_require__("../../../common/esm2015/http.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__shared_dataService__ = __webpack_require__("../../../../../ClientApp/app/shared/dataService.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__shared_optionposition__ = __webpack_require__("../../../../../ClientApp/app/shared/optionposition.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4_moment__ = __webpack_require__("../../../../moment/moment.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_4_moment___default = __webpack_require__.n(__WEBPACK_IMPORTED_MODULE_4_moment__);
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};





let Matrix = class Matrix {
    constructor(http, dataService) {
        this.http = http;
        this.dataService = dataService;
        this.matrix_Calls = new Map();
        this.matrix_Puts = new Map();
        this.dateIndex = 0;
        this.positionSelect.bind(this);
        //Subscribe to Commit Trade event
        this.dataService.getMessage().subscribe(msg => {
            this.commitTrades();
        });
        //Subscribe to backtest controls
        this.dataService.getBacktestUpdate().subscribe(msg => {
            this.updateMatrix();
        });
    }
    //private positionsToCommit = new Map();
    ngOnInit() {
        //Get available backtest dates
        this.http.get('getbacktestdates').subscribe(data => {
            this.dataService.backtestDateStream = data;
            this.updateMatrix();
        });
    }
    updateMatrix() {
        let backtestDate = this.dataService.getCurrentBacktestDate();
        this.http.get('getnewdata?id=' + backtestDate).subscribe(data => {
            this.parseData(data);
            this.updatePortfolioMetrics();
        });
    }
    parseData(data) {
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
            let a = __WEBPACK_IMPORTED_MODULE_4_moment__(this.dataService.getCurrentBacktestDate(), "YYYY/MM/DD hh:mm:ss");
            let b = __WEBPACK_IMPORTED_MODULE_4_moment__(dateKeys[_i]);
            var diffDays = b.diff(a, 'days');
            var dateHeader = document.createElement('th');
            dateHeader.innerHTML = dateKeys[_i] + " (DTE " + diffDays + ")";
            headerElem.appendChild(dateHeader);
        }
        this.fillOptionTables('Call', dateKeys, data);
        this.fillOptionTables('Put', dateKeys, data);
    }
    fillOptionTables(selectorPrefix, dateKeys, data) {
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
        let targetType;
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
    positionDeSelect(evnt) {
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
            let tempPosition = new __WEBPACK_IMPORTED_MODULE_3__shared_optionposition__["a" /* OptionPosition */];
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
    positionSelect(evnt, selectorPrefix) {
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
        }
        else {
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
    commitTrades() {
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
            let newUnits = parseInt($(newPosition).children()[2].innerHTML);
            if ($(newPosition).hasClass('positionActive')) {
                //Position already exists, close if units = 0
                var posIndex = this.getPositionIndex(expDate, strike, optionType);
                newPositionUnits = newUnits + this.dataService.curPositions[posIndex].units;
                if (newPositionUnits == 0) {
                    //Close Position
                    let realisedPnL = (this.dataService.curPositions[posIndex].curPrice - this.dataService.curPositions[posIndex].entryPrice) * this.dataService.curPositions[posIndex].units * 100;
                    this.dataService.realisedPnL += realisedPnL;
                    this.dataService.curPositions.splice(posIndex, 1);
                }
                else {
                    this.dataService.curPositions[posIndex].units = newPositionUnits;
                }
            }
            else {
                //Add new position to existing positions array 
                let tempPosition = new __WEBPACK_IMPORTED_MODULE_3__shared_optionposition__["a" /* OptionPosition */];
                if (optionType == "Call") {
                    tempPosition.curPrice = this.matrix_Calls.get(expDate)[rowIndex]["marketPrice"];
                    tempPosition.entryPrice = this.matrix_Calls.get(expDate)[rowIndex]["marketPrice"];
                }
                else if (optionType == "Put") {
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
    updatePortfolioMetrics() {
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
    getRowMetaData(row) {
        let metaData = row.split(";", 3);
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
    callTableScroll() {
        let scrollVal = document.getElementById("callContainer_Options02").scrollTop;
        document.getElementById("callContainer_Options00").scrollTop = scrollVal;
        document.getElementById("callContainer_Options01").scrollTop = scrollVal;
        document.getElementById("callContainer_Strikes").scrollTop = scrollVal;
    }
    putTableScroll() {
        let scrollVal = document.getElementById("putContainer_Options02").scrollTop;
        document.getElementById("putContainer_Options00").scrollTop = scrollVal;
        document.getElementById("putContainer_Options01").scrollTop = scrollVal;
        document.getElementById("putContainer_Strikes").scrollTop = scrollVal;
    }
};
Matrix = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["m" /* Component */])({
        selector: "matrix",
        template: __webpack_require__("../../../../../ClientApp/app/matrix/matrix.component.html"),
        styles: [__webpack_require__("../../../../../ClientApp/app/matrix/matrix.component.css")]
    }),
    __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_1__angular_common_http__["a" /* HttpClient */], __WEBPACK_IMPORTED_MODULE_2__shared_dataService__["a" /* DataService */]])
], Matrix);



/***/ }),

/***/ "../../../../../ClientApp/app/metrics_sidebar/metrics_sidebar.component.html":
/***/ (function(module, exports) {

module.exports = "\r\n<div>\r\n    <button id=\"prevDateBtn\" (click)=\"revertBacktestBtn()\" class=\"btn btn-warning\"><</button>\r\n    <button id=\"nextDateBtn\" (click)=\"progressBacktestBtn()\" class=\"btn btn-warning\">></button>\r\n    <label id=\"dateLabel\">{{ currentDate }}</label>\r\n</div>\r\n<div>\r\n    <h5 style=\"display:inline-block\" id=\"navLabel\">NAV: </h5>\r\n    <h5 style=\"display:inline-block;  background-color:hotpink\" id=\"navValue\">{{ currentNav | currency:'USD':true }}</h5>\r\n    <div *ngIf=\"newPositionsval\" style=\"display:inline-block; background-color:greenyellow\">\r\n        <h5 style=\"display:inline-block\" id=\"newPositionsLabel\"> + </h5>\r\n        <h5 style=\"display:inline-block\" id=\"newPositionsValue\">{{ newPositionsval | currency:'USD':true }}</h5>\r\n    </div>\r\n</div>\r\n<div>\r\n    <h5 id=\"unRealisedPnlLabel\" style=\"display:inline-block\">Unrealised PnL: </h5>\r\n    <h5 id=\"unRealisedPnlValue\" style=\"display:inline-block\">{{ unRealisedPnL | currency:'USD':true }}</h5>\r\n</div>\r\n<div>\r\n    <h5 id=\"realisedPnlLabel\" style=\"display:inline-block\">Realised PnL: </h5>\r\n    <h5 id=\"realisedPnlValue\" style=\"display:inline-block;  background-color:lightskyblue\">{{ realisedPnL | currency:'USD':true }}</h5>\r\n</div>\r\n<button (click)=\"commitTradesBtn()\" class=\"btn btn-success\">Commit</button>\r\n"

/***/ }),

/***/ "../../../../../ClientApp/app/metrics_sidebar/metrics_sidebar.component.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return MetricsSidebar; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__shared_dataService__ = __webpack_require__("../../../../../ClientApp/app/shared/dataService.ts");
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};


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
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["m" /* Component */])({
        selector: "metrics_sidebar",
        template: __webpack_require__("../../../../../ClientApp/app/metrics_sidebar/metrics_sidebar.component.html"),
        styles: []
    }),
    __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_1__shared_dataService__["a" /* DataService */]])
], MetricsSidebar);



/***/ }),

/***/ "../../../../../ClientApp/app/profile/profile.component.html":
/***/ (function(module, exports) {

module.exports = "<div id=\"chart\"></div>"

/***/ }),

/***/ "../../../../../ClientApp/app/profile/profile.component.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return Profile; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__shared_dataService__ = __webpack_require__("../../../../../ClientApp/app/shared/dataService.ts");
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
var __metadata = (this && this.__metadata) || function (k, v) {
    if (typeof Reflect === "object" && typeof Reflect.metadata === "function") return Reflect.metadata(k, v);
};


let Profile = class Profile {
    constructor(dataService) {
        this.dataService = dataService;
        this.chartLayout = {
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
        this.underlyingStrikes = [];
        this.dataService.getPortfolioUpdate().subscribe(vals => {
            this.updateProfile();
        });
        for (var _i = 900; _i < 1300; _i += 10) {
            this.underlyingStrikes.push(_i);
        }
    }
    ngOnInit() {
        var posData = {
            x: [],
            y: [],
            type: 'scatter'
        };
        var data = [posData];
        this.chartContainer = $('#chart')[0];
        Plotly.newPlot(this.chartContainer, data, this.chartLayout);
    }
    updateProfile() {
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
        };
        var data = [posData, tPlusX];
        Plotly.newPlot(this.chartContainer, data, this.chartLayout);
    }
    CND(x) {
        if (x < 0) {
            return (1 - this.CND(-x));
        }
        else {
            let k = 1 / (1 + .2316419 * x);
            return (1 - Math.exp(-x * x / 2) / Math.sqrt(2 * Math.PI) * k * (.31938153 + k * (-.356563782 + k * (1.781477937 + k * (-1.821255978 + k * 1.330274429)))));
        }
    }
    BlackScholes(PutCallFlag, S, X, T, r, v) {
        let d1 = (Math.log(S / X) + (r + v * v / 2) * T) / (v * Math.sqrt(T));
        let d2 = d1 - v * Math.sqrt(T);
        if (PutCallFlag === "call") {
            return (S * this.CND(d1) - X * Math.exp(-r * T) * this.CND(d2));
        }
        else {
            return (X * Math.exp(-r * T) * this.CND(-d2) - S * this.CND(-d1));
        }
    }
};
Profile = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["m" /* Component */])({
        selector: "profile",
        template: __webpack_require__("../../../../../ClientApp/app/profile/profile.component.html"),
        styleUrls: []
    }),
    __metadata("design:paramtypes", [__WEBPACK_IMPORTED_MODULE_1__shared_dataService__["a" /* DataService */]])
], Profile);



/***/ }),

/***/ "../../../../../ClientApp/app/shared/dataService.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return DataService; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0_rxjs_Subject__ = __webpack_require__("../../../../rxjs/_esm2015/Subject.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2_rxjs_add_operator_map__ = __webpack_require__("../../../../rxjs/_esm2015/add/operator/map.js");
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};



let DataService = class DataService {
    constructor() {
        this.realisedPnL = 0;
        this.backtestDateIndex = 0;
        this.curPositions = [];
        this.positionsToCommit = new Map();
        //Subjects
        this.subject = new __WEBPACK_IMPORTED_MODULE_0_rxjs_Subject__["a" /* Subject */]();
        this.portfolioUpdateSubject = new __WEBPACK_IMPORTED_MODULE_0_rxjs_Subject__["a" /* Subject */]();
        this.backtestUpdateSubject = new __WEBPACK_IMPORTED_MODULE_0_rxjs_Subject__["a" /* Subject */]();
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
    Object(__WEBPACK_IMPORTED_MODULE_1__angular_core__["w" /* Injectable */])()
], DataService);



/***/ }),

/***/ "../../../../../ClientApp/app/shared/optionposition.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
class OptionPosition {
    constructor() { }
}
/* harmony export (immutable) */ __webpack_exports__["a"] = OptionPosition;



/***/ }),

/***/ "../../../../../ClientApp/app/shop/productList.component.html":
/***/ (function(module, exports) {

module.exports = "<div>\r\n    <ul>\r\n        <li *ngFor=\"let p of Products\">{{ p.title }}: {{ p.price | currency:\"USD\":true }}</li>\r\n    </ul>\r\n</div>"

/***/ }),

/***/ "../../../../../ClientApp/app/shop/productList.component.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, "a", function() { return ProductList; });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};

let ProductList = class ProductList {
};
ProductList = __decorate([
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["m" /* Component */])({
        selector: "product-list",
        template: __webpack_require__("../../../../../ClientApp/app/shop/productList.component.html"),
        styles: []
    })
], ProductList);



/***/ }),

/***/ "../../../../../ClientApp/environments/environment.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
// The file contents for the current environment will overwrite these during build.
// The build system defaults to the dev environment which uses `environment.ts`, but if you do
// `ng build --env=prod` then `environment.prod.ts` will be used instead.
// The list of which env maps to which file can be found in `.angular-cli.json`.
const environment = {
    production: false
};
/* harmony export (immutable) */ __webpack_exports__["a"] = environment;



/***/ }),

/***/ "../../../../../ClientApp/main.ts":
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
Object.defineProperty(__webpack_exports__, "__esModule", { value: true });
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_0__angular_core__ = __webpack_require__("../../../core/esm2015/core.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_1__angular_platform_browser_dynamic__ = __webpack_require__("../../../platform-browser-dynamic/esm2015/platform-browser-dynamic.js");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_2__app_app_module__ = __webpack_require__("../../../../../ClientApp/app/app.module.ts");
/* harmony import */ var __WEBPACK_IMPORTED_MODULE_3__environments_environment__ = __webpack_require__("../../../../../ClientApp/environments/environment.ts");




if (__WEBPACK_IMPORTED_MODULE_3__environments_environment__["a" /* environment */].production) {
    Object(__WEBPACK_IMPORTED_MODULE_0__angular_core__["_5" /* enableProdMode */])();
}
Object(__WEBPACK_IMPORTED_MODULE_1__angular_platform_browser_dynamic__["a" /* platformBrowserDynamic */])().bootstrapModule(__WEBPACK_IMPORTED_MODULE_2__app_app_module__["a" /* AppModule */])
    .catch(err => console.log(err));


/***/ }),

/***/ "../../../../moment/locale recursive ^\\.\\/.*$":
/***/ (function(module, exports, __webpack_require__) {

var map = {
	"./af": "../../../../moment/locale/af.js",
	"./af.js": "../../../../moment/locale/af.js",
	"./ar": "../../../../moment/locale/ar.js",
	"./ar-dz": "../../../../moment/locale/ar-dz.js",
	"./ar-dz.js": "../../../../moment/locale/ar-dz.js",
	"./ar-kw": "../../../../moment/locale/ar-kw.js",
	"./ar-kw.js": "../../../../moment/locale/ar-kw.js",
	"./ar-ly": "../../../../moment/locale/ar-ly.js",
	"./ar-ly.js": "../../../../moment/locale/ar-ly.js",
	"./ar-ma": "../../../../moment/locale/ar-ma.js",
	"./ar-ma.js": "../../../../moment/locale/ar-ma.js",
	"./ar-sa": "../../../../moment/locale/ar-sa.js",
	"./ar-sa.js": "../../../../moment/locale/ar-sa.js",
	"./ar-tn": "../../../../moment/locale/ar-tn.js",
	"./ar-tn.js": "../../../../moment/locale/ar-tn.js",
	"./ar.js": "../../../../moment/locale/ar.js",
	"./az": "../../../../moment/locale/az.js",
	"./az.js": "../../../../moment/locale/az.js",
	"./be": "../../../../moment/locale/be.js",
	"./be.js": "../../../../moment/locale/be.js",
	"./bg": "../../../../moment/locale/bg.js",
	"./bg.js": "../../../../moment/locale/bg.js",
	"./bm": "../../../../moment/locale/bm.js",
	"./bm.js": "../../../../moment/locale/bm.js",
	"./bn": "../../../../moment/locale/bn.js",
	"./bn.js": "../../../../moment/locale/bn.js",
	"./bo": "../../../../moment/locale/bo.js",
	"./bo.js": "../../../../moment/locale/bo.js",
	"./br": "../../../../moment/locale/br.js",
	"./br.js": "../../../../moment/locale/br.js",
	"./bs": "../../../../moment/locale/bs.js",
	"./bs.js": "../../../../moment/locale/bs.js",
	"./ca": "../../../../moment/locale/ca.js",
	"./ca.js": "../../../../moment/locale/ca.js",
	"./cs": "../../../../moment/locale/cs.js",
	"./cs.js": "../../../../moment/locale/cs.js",
	"./cv": "../../../../moment/locale/cv.js",
	"./cv.js": "../../../../moment/locale/cv.js",
	"./cy": "../../../../moment/locale/cy.js",
	"./cy.js": "../../../../moment/locale/cy.js",
	"./da": "../../../../moment/locale/da.js",
	"./da.js": "../../../../moment/locale/da.js",
	"./de": "../../../../moment/locale/de.js",
	"./de-at": "../../../../moment/locale/de-at.js",
	"./de-at.js": "../../../../moment/locale/de-at.js",
	"./de-ch": "../../../../moment/locale/de-ch.js",
	"./de-ch.js": "../../../../moment/locale/de-ch.js",
	"./de.js": "../../../../moment/locale/de.js",
	"./dv": "../../../../moment/locale/dv.js",
	"./dv.js": "../../../../moment/locale/dv.js",
	"./el": "../../../../moment/locale/el.js",
	"./el.js": "../../../../moment/locale/el.js",
	"./en-au": "../../../../moment/locale/en-au.js",
	"./en-au.js": "../../../../moment/locale/en-au.js",
	"./en-ca": "../../../../moment/locale/en-ca.js",
	"./en-ca.js": "../../../../moment/locale/en-ca.js",
	"./en-gb": "../../../../moment/locale/en-gb.js",
	"./en-gb.js": "../../../../moment/locale/en-gb.js",
	"./en-ie": "../../../../moment/locale/en-ie.js",
	"./en-ie.js": "../../../../moment/locale/en-ie.js",
	"./en-nz": "../../../../moment/locale/en-nz.js",
	"./en-nz.js": "../../../../moment/locale/en-nz.js",
	"./eo": "../../../../moment/locale/eo.js",
	"./eo.js": "../../../../moment/locale/eo.js",
	"./es": "../../../../moment/locale/es.js",
	"./es-do": "../../../../moment/locale/es-do.js",
	"./es-do.js": "../../../../moment/locale/es-do.js",
	"./es-us": "../../../../moment/locale/es-us.js",
	"./es-us.js": "../../../../moment/locale/es-us.js",
	"./es.js": "../../../../moment/locale/es.js",
	"./et": "../../../../moment/locale/et.js",
	"./et.js": "../../../../moment/locale/et.js",
	"./eu": "../../../../moment/locale/eu.js",
	"./eu.js": "../../../../moment/locale/eu.js",
	"./fa": "../../../../moment/locale/fa.js",
	"./fa.js": "../../../../moment/locale/fa.js",
	"./fi": "../../../../moment/locale/fi.js",
	"./fi.js": "../../../../moment/locale/fi.js",
	"./fo": "../../../../moment/locale/fo.js",
	"./fo.js": "../../../../moment/locale/fo.js",
	"./fr": "../../../../moment/locale/fr.js",
	"./fr-ca": "../../../../moment/locale/fr-ca.js",
	"./fr-ca.js": "../../../../moment/locale/fr-ca.js",
	"./fr-ch": "../../../../moment/locale/fr-ch.js",
	"./fr-ch.js": "../../../../moment/locale/fr-ch.js",
	"./fr.js": "../../../../moment/locale/fr.js",
	"./fy": "../../../../moment/locale/fy.js",
	"./fy.js": "../../../../moment/locale/fy.js",
	"./gd": "../../../../moment/locale/gd.js",
	"./gd.js": "../../../../moment/locale/gd.js",
	"./gl": "../../../../moment/locale/gl.js",
	"./gl.js": "../../../../moment/locale/gl.js",
	"./gom-latn": "../../../../moment/locale/gom-latn.js",
	"./gom-latn.js": "../../../../moment/locale/gom-latn.js",
	"./gu": "../../../../moment/locale/gu.js",
	"./gu.js": "../../../../moment/locale/gu.js",
	"./he": "../../../../moment/locale/he.js",
	"./he.js": "../../../../moment/locale/he.js",
	"./hi": "../../../../moment/locale/hi.js",
	"./hi.js": "../../../../moment/locale/hi.js",
	"./hr": "../../../../moment/locale/hr.js",
	"./hr.js": "../../../../moment/locale/hr.js",
	"./hu": "../../../../moment/locale/hu.js",
	"./hu.js": "../../../../moment/locale/hu.js",
	"./hy-am": "../../../../moment/locale/hy-am.js",
	"./hy-am.js": "../../../../moment/locale/hy-am.js",
	"./id": "../../../../moment/locale/id.js",
	"./id.js": "../../../../moment/locale/id.js",
	"./is": "../../../../moment/locale/is.js",
	"./is.js": "../../../../moment/locale/is.js",
	"./it": "../../../../moment/locale/it.js",
	"./it.js": "../../../../moment/locale/it.js",
	"./ja": "../../../../moment/locale/ja.js",
	"./ja.js": "../../../../moment/locale/ja.js",
	"./jv": "../../../../moment/locale/jv.js",
	"./jv.js": "../../../../moment/locale/jv.js",
	"./ka": "../../../../moment/locale/ka.js",
	"./ka.js": "../../../../moment/locale/ka.js",
	"./kk": "../../../../moment/locale/kk.js",
	"./kk.js": "../../../../moment/locale/kk.js",
	"./km": "../../../../moment/locale/km.js",
	"./km.js": "../../../../moment/locale/km.js",
	"./kn": "../../../../moment/locale/kn.js",
	"./kn.js": "../../../../moment/locale/kn.js",
	"./ko": "../../../../moment/locale/ko.js",
	"./ko.js": "../../../../moment/locale/ko.js",
	"./ky": "../../../../moment/locale/ky.js",
	"./ky.js": "../../../../moment/locale/ky.js",
	"./lb": "../../../../moment/locale/lb.js",
	"./lb.js": "../../../../moment/locale/lb.js",
	"./lo": "../../../../moment/locale/lo.js",
	"./lo.js": "../../../../moment/locale/lo.js",
	"./lt": "../../../../moment/locale/lt.js",
	"./lt.js": "../../../../moment/locale/lt.js",
	"./lv": "../../../../moment/locale/lv.js",
	"./lv.js": "../../../../moment/locale/lv.js",
	"./me": "../../../../moment/locale/me.js",
	"./me.js": "../../../../moment/locale/me.js",
	"./mi": "../../../../moment/locale/mi.js",
	"./mi.js": "../../../../moment/locale/mi.js",
	"./mk": "../../../../moment/locale/mk.js",
	"./mk.js": "../../../../moment/locale/mk.js",
	"./ml": "../../../../moment/locale/ml.js",
	"./ml.js": "../../../../moment/locale/ml.js",
	"./mr": "../../../../moment/locale/mr.js",
	"./mr.js": "../../../../moment/locale/mr.js",
	"./ms": "../../../../moment/locale/ms.js",
	"./ms-my": "../../../../moment/locale/ms-my.js",
	"./ms-my.js": "../../../../moment/locale/ms-my.js",
	"./ms.js": "../../../../moment/locale/ms.js",
	"./mt": "../../../../moment/locale/mt.js",
	"./mt.js": "../../../../moment/locale/mt.js",
	"./my": "../../../../moment/locale/my.js",
	"./my.js": "../../../../moment/locale/my.js",
	"./nb": "../../../../moment/locale/nb.js",
	"./nb.js": "../../../../moment/locale/nb.js",
	"./ne": "../../../../moment/locale/ne.js",
	"./ne.js": "../../../../moment/locale/ne.js",
	"./nl": "../../../../moment/locale/nl.js",
	"./nl-be": "../../../../moment/locale/nl-be.js",
	"./nl-be.js": "../../../../moment/locale/nl-be.js",
	"./nl.js": "../../../../moment/locale/nl.js",
	"./nn": "../../../../moment/locale/nn.js",
	"./nn.js": "../../../../moment/locale/nn.js",
	"./pa-in": "../../../../moment/locale/pa-in.js",
	"./pa-in.js": "../../../../moment/locale/pa-in.js",
	"./pl": "../../../../moment/locale/pl.js",
	"./pl.js": "../../../../moment/locale/pl.js",
	"./pt": "../../../../moment/locale/pt.js",
	"./pt-br": "../../../../moment/locale/pt-br.js",
	"./pt-br.js": "../../../../moment/locale/pt-br.js",
	"./pt.js": "../../../../moment/locale/pt.js",
	"./ro": "../../../../moment/locale/ro.js",
	"./ro.js": "../../../../moment/locale/ro.js",
	"./ru": "../../../../moment/locale/ru.js",
	"./ru.js": "../../../../moment/locale/ru.js",
	"./sd": "../../../../moment/locale/sd.js",
	"./sd.js": "../../../../moment/locale/sd.js",
	"./se": "../../../../moment/locale/se.js",
	"./se.js": "../../../../moment/locale/se.js",
	"./si": "../../../../moment/locale/si.js",
	"./si.js": "../../../../moment/locale/si.js",
	"./sk": "../../../../moment/locale/sk.js",
	"./sk.js": "../../../../moment/locale/sk.js",
	"./sl": "../../../../moment/locale/sl.js",
	"./sl.js": "../../../../moment/locale/sl.js",
	"./sq": "../../../../moment/locale/sq.js",
	"./sq.js": "../../../../moment/locale/sq.js",
	"./sr": "../../../../moment/locale/sr.js",
	"./sr-cyrl": "../../../../moment/locale/sr-cyrl.js",
	"./sr-cyrl.js": "../../../../moment/locale/sr-cyrl.js",
	"./sr.js": "../../../../moment/locale/sr.js",
	"./ss": "../../../../moment/locale/ss.js",
	"./ss.js": "../../../../moment/locale/ss.js",
	"./sv": "../../../../moment/locale/sv.js",
	"./sv.js": "../../../../moment/locale/sv.js",
	"./sw": "../../../../moment/locale/sw.js",
	"./sw.js": "../../../../moment/locale/sw.js",
	"./ta": "../../../../moment/locale/ta.js",
	"./ta.js": "../../../../moment/locale/ta.js",
	"./te": "../../../../moment/locale/te.js",
	"./te.js": "../../../../moment/locale/te.js",
	"./tet": "../../../../moment/locale/tet.js",
	"./tet.js": "../../../../moment/locale/tet.js",
	"./th": "../../../../moment/locale/th.js",
	"./th.js": "../../../../moment/locale/th.js",
	"./tl-ph": "../../../../moment/locale/tl-ph.js",
	"./tl-ph.js": "../../../../moment/locale/tl-ph.js",
	"./tlh": "../../../../moment/locale/tlh.js",
	"./tlh.js": "../../../../moment/locale/tlh.js",
	"./tr": "../../../../moment/locale/tr.js",
	"./tr.js": "../../../../moment/locale/tr.js",
	"./tzl": "../../../../moment/locale/tzl.js",
	"./tzl.js": "../../../../moment/locale/tzl.js",
	"./tzm": "../../../../moment/locale/tzm.js",
	"./tzm-latn": "../../../../moment/locale/tzm-latn.js",
	"./tzm-latn.js": "../../../../moment/locale/tzm-latn.js",
	"./tzm.js": "../../../../moment/locale/tzm.js",
	"./uk": "../../../../moment/locale/uk.js",
	"./uk.js": "../../../../moment/locale/uk.js",
	"./ur": "../../../../moment/locale/ur.js",
	"./ur.js": "../../../../moment/locale/ur.js",
	"./uz": "../../../../moment/locale/uz.js",
	"./uz-latn": "../../../../moment/locale/uz-latn.js",
	"./uz-latn.js": "../../../../moment/locale/uz-latn.js",
	"./uz.js": "../../../../moment/locale/uz.js",
	"./vi": "../../../../moment/locale/vi.js",
	"./vi.js": "../../../../moment/locale/vi.js",
	"./x-pseudo": "../../../../moment/locale/x-pseudo.js",
	"./x-pseudo.js": "../../../../moment/locale/x-pseudo.js",
	"./yo": "../../../../moment/locale/yo.js",
	"./yo.js": "../../../../moment/locale/yo.js",
	"./zh-cn": "../../../../moment/locale/zh-cn.js",
	"./zh-cn.js": "../../../../moment/locale/zh-cn.js",
	"./zh-hk": "../../../../moment/locale/zh-hk.js",
	"./zh-hk.js": "../../../../moment/locale/zh-hk.js",
	"./zh-tw": "../../../../moment/locale/zh-tw.js",
	"./zh-tw.js": "../../../../moment/locale/zh-tw.js"
};
function webpackContext(req) {
	return __webpack_require__(webpackContextResolve(req));
};
function webpackContextResolve(req) {
	var id = map[req];
	if(!(id + 1)) // check for number or string
		throw new Error("Cannot find module '" + req + "'.");
	return id;
};
webpackContext.keys = function webpackContextKeys() {
	return Object.keys(map);
};
webpackContext.resolve = webpackContextResolve;
module.exports = webpackContext;
webpackContext.id = "../../../../moment/locale recursive ^\\.\\/.*$";

/***/ }),

/***/ 0:
/***/ (function(module, exports, __webpack_require__) {

module.exports = __webpack_require__("../../../../../ClientApp/main.ts");


/***/ })

},[0]);
//# sourceMappingURL=main.bundle.js.map