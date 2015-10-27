/**
* This class implements the methods in graph.h
*/
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include "graph.h"
#include "ui_graph.h"

using namespace std;

//constructor
graph::graph()
{
}

//
graph::graph(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::graph)
{
    ui->setupUi(this);
    graph::makePlot();
}

graph::~graph()
{
    delete ui;
}
//

/*Prepares the data needed to graph from the publications summary.
*/
void graph:: preparePublications(string name, list<string> types, list<int> years, int diff_types, int begin, int end, int graphtype)
{
	list<string> t = types;	//create a copy to manipulate
	list<int> y = years;	//create a copy to manipulate
	string compare;			//for checking when a new type of publication exists
	int track = 0;				//used to track where in the string array we are

	int size = types.size(); //get the size of the list
	int num_publications = 0;//number of publications that fit the date range. used for y-axis

	vector<int> xaxis;		//array for the number of publications of each publication type
	vector<string> xlabel;	//string array for x-axis tick labels


								//initialize the array values to 0 to prepare for counting
	for (int count = 0; count < diff_types; count++)
	{
		xaxis[count] = 0;
	}


	compare = t.front();	//the first publication type
	xlabel[0] = t.front();	//record the first label

							//This loop goes through the list of publications and counts how many are of each type.
	for (int count = 0; count < size; count++)
	{
		//check if the publications is in the date range
		if ((y.front() >= begin) && (y.front() <= end))
		{
			//check if the publication type is the same as the previous
			if (t.front() == compare)
			{
				//record the publication
				xaxis[track]++;
				//pop from the list
				t.pop_front();
				y.pop_front();
			}
			//else start counting the next type
			else
			{
				//record the publication for the new type
				track++;
				xaxis[track]++;
				//record the label for the new type
				xlabel[track] = t.front();

				//pop from the list
				t.pop_front();
				y.pop_front();
				//record the new publication type
				compare = t.front();
			}
		}
		else
		{
			//pop from the list
			t.pop_front();
			y.pop_front();
		}
	}


	/* THE TYPE OF GRAPH THAT THE USER WANTS TO DISPLAY
	*    1 = bar
	*    2 = pie
	*    3 = line
	*/
	if (graphtype == 1)
		createBarPublications(name, num_publications, xaxis, xlabel);
	else  (graphtype == 2)
		createLinePublications(name, num_publications, xaxis, xlabel);
	
}



//method for creating a window which displays a bar graph from the Publications summary
void graph:: createBarPublications(string name, int num_publications, vector<int> xaxis, vector<string> xlabel)
{
	
    // empty bar chart objects:
    
    QCPBars *Person = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    
    
    ui->customPlot->addPlottable(Person);
    
    // set names and colors:
    QPen pen;
    pen.setWidthF(1.0);
    
    
    Person->setName(<< name << );
    pen.setColor(QColor(1, 92, 191));
    Person->setPen(pen);
    Person->setBrush(QColor(1, 92, 191, 50));
    
    //stack bars ontop of each other:
    
    
    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    for (int i = 0 ; i <= xaxis ; i++)
    {
        ticks << array[i];  //a loop to print out the ticks
    }
    
    // loop to print the labels
    int len = xlabel.length();
    for(int i = 0; i < len; i++)
    {
        labels <<stars[i] << ;
    }
    
}
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(labels);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTickCount(0);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setLabel("Type of Publication ");
    
    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, num_publications);

    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Number of Publication ");
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui->customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->customPlot->yAxis->grid()->setSubGridPen(gridPen);
    
    // Add data:
    QVector<double> PersonData;
    
    PersonData << 1 << 3 << 2 << 5 << 6 << 8 << 12;
    //it will be loop
    
    Person->setData(ticks, nuclearData);
    
    
    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui->customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    
    

}

//method for creating a window which displays a line graph from the Publications summary
void graph:: createLinePublications(string name, int num_publications, vector<int> xaxis, vector<string> xlabel)
{
    
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(QColor(1, 92, 191));
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(2.5);
    ui->customPlot->graph()->setPen(pen);
    
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QPixmap("./sun.png")));
    
    // set data:
    QVector<double> year, value;
    for (int i = 0 ; i <= xaxis ; i++)
    {
        year << array[i];  //a loop to print out the ticks
    }
    
    value << 2.17 << 3.42 << 4.94 << 10.38 << 15.86 << 29.33;
    ui->customPlot->graph()->setData(year, value);
    
    // set title of plot:
    ui->customPlot->plotLayout()->insertRow(0);
    ui->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->customPlot, << name <<));
    // set a fixed tick-step to one tick per year value:
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(1);
    ui->customPlot->xAxis->setSubTickCount(3);
    // other axis configurations:
    ui->customPlot->xAxis->setLabel("Type of Publication");
    ui->customPlot->yAxis->setLabel("Number of Publication");
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setTickLabels(false);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->xAxis2->setSubTickCount(0);
    ui->customPlot->yAxis2->setSubTickCount(0);
    ui->customPlot->xAxis->setRange(2000, 2015);
    ui->customPlot->yAxis->setRange(0, << num_publications <<);
    

}





