/*
	It is not necessary to make the strategy a member of the class, you can simply pass it as a pointer to the
	function that will invoke it.
*/



/*

Instead of doing
model.SetFormat(&csv);
model.Export();


int main() {
	DataModel model{};

	// model.AddRow({1, 2, 3, 4});
	// model.AddRow({11, 12, 13, 14});

	model.Load();
	model.Display();
	// model.Save();

	CSVFormat csv{"records.csv"};

	model.SetFormat(&csv);
	model.Export();

	HtmlFormat html{"records.html"};

	model.SetFormat(&html);
	model.Export();

	return 0;
}

*/


int main() {
	DataModel model{};

	// model.AddRow({1, 2, 3, 4});
	// model.AddRow({11, 12, 13, 14});

	model.Load();
	model.Display();
	// model.Save();

	CSVFormat csv{"records.csv"};
	HtmlFormat html{"records.html"};

	model.Export(&csv);
	model.Export(&html);

	return 0;
}