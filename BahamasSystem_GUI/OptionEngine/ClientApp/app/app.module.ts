import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from "@angular/common/http";

import { AppComponent } from './app.component';
import { ProductList } from './shop/productList.component';
import { DataService } from "./shared/dataService";
import { MetricsSidebar } from "./metrics_sidebar/metrics_sidebar.component";
import { Matrix } from "./matrix/matrix.component";
import { Profile } from "./profile/profile.component";
import {CodeEditor } from "./code_editor/code_editor.component";

@NgModule({
    declarations: [
        AppComponent,
        ProductList,
        MetricsSidebar,
        Matrix,
        Profile,
        CodeEditor
    ],
    imports: [
        BrowserModule,
        HttpClientModule
    ],
    providers: [
        DataService
    ],
    bootstrap: [AppComponent]
})
export class AppModule { }
