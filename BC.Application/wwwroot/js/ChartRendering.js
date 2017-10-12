function DrawChart() {
    $.ajax({
        url: ChartSettings.DataSource,
        type: 'GET',
        dataType: 'json',
        success: function (d) {

            margin = {
                top: 20,
                right: 20,
                bottom: 20,
                left: 45
            };

            width = ChartSettings.ChartHeight - margin.left - margin.right;
            height = ChartSettings.ChartWidth - margin.top - margin.bottom;

            var data = new Array();

            $.each(d, function (index, item) {
                data.push(item);
            });

            var x = d3.time.scale()
                .domain(d3.extent(data, function (d) {
                    return new Date(d.date);
                }))
                .rangeRound([0, width]);

            var y = d3.scale.linear()
                .domain([0, 5])
                .range([height, 0]);

            var line = d3.svg.line()
                .x(function (d) {
                    return x(d.date);
                })
                .y(function (d) {
                    return y(d.value);
                });

            var zoom = d3.behavior.zoom()
                .x(x)
                .y(y)
                .on("zoom", zoomed);

            svg = d3.select('#chart')
                .append("svg:svg")
                .attr('width', width + margin.left + margin.right)
                .attr('height', height + margin.top + margin.bottom)
                .call(zoom)
                .append("svg:g")
                .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

            var make_x_axis = function () {
                return d3.svg.axis()
                    .scale(x)
                    .orient("bottom")
                    .ticks(5);
            };

            var make_y_axis = function () {
                return d3.svg.axis()
                    .scale(y)
                    .orient("left")
                    .ticks(5);
            };

            var xAxis = d3.svg.axis()
                .scale(x)
                .orient("bottom");

            svg.append("svg:g")
                .attr("class", "x axis")
                .attr("transform", "translate(0, " + height + ")")
                .call(xAxis);

            var yAxis = d3.svg.axis()
                .scale(y)
                .orient("left")
                .ticks(5);

            svg.append("g")
                .attr("class", "y axis")
                .call(yAxis);

            svg.append("g")
                .attr("class", "x grid")
                .attr("transform", "translate(0," + height + ")")
                .call(make_x_axis()
                    .tickSize(-height, 0, 0)
                    .tickFormat(""));

            svg.append("g")
                .attr("class", "y grid")
                .call(make_y_axis()
                    .tickSize(-width, 0, 0)
                    .tickFormat(""));

            var clip = svg.append("svg:clipPath")
                .attr("id", "clip")
                .append("svg:rect")
                .attr("x", 0)
                .attr("y", 0)
                .attr("width", width)
                .attr("height", height);

            var chartBody = svg.append("g")
                .attr("clip-path", "url(#clip)");

            chartBody.append("svg:path")
                .datum(data)
                .attr("class", "line")
                .attr("d", line);

            function zoomed() {
                svg.select(".x.axis").call(xAxis);
                svg.select(".y.axis").call(yAxis);
                svg.select(".x.grid")
                    .call(make_x_axis()
                        .tickSize(-height, 0, 0)
                        .tickFormat(""));
                svg.select(".y.grid")
                    .call(make_y_axis()
                        .tickSize(-width, 0, 0)
                        .tickFormat(""));
                svg.select(".line")
                    .attr("class", "line")
                    .attr("d", line);
            }
        },
        error: function (xhr, ajaxOptions, thrownError) {
            alert(xhr.status);
            alert(thrownError);
        }
    });

}