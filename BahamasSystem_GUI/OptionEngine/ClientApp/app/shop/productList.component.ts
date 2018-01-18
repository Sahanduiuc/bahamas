import { Component, OnInit } from '@angular/core';
import { DataService } from "../shared/dataService";
import { Product } from "../shared/product";

@Component({
    selector: "product-list",
    templateUrl: "./productList.component.html",
    styles: []
})
export class ProductList{
    //constructor(private data: DataService) {
    //    this.Products = data.Products;
    //}

    //public Products: Product[] = [];

    //ngOnInit(): void {
    //    this.data.loadProducts()
    //        .subscribe();
    //}
}