//input: Tyy, Txx, TR, image;
//output:    Hlong error_number;




	Hobject tai, region_tai, mean_tai, white_tai, connect_tai, select_tai,em_tai, union_tai, dila_tai, ske_tai, error_tai, err;

	Hobject c1, c2, diff_taia, region_taia;

	gen_circle(&tai, Tyy, Txx, TR-90);
	change_domain (image, tai, &region_tai);
	mean_image (region_tai, &mean_tai, 2, 2);
	threshold (mean_tai, &white_tai, 189, 255);
	connection (white_tai, &connect_tai);
	select_shape (connect_tai, &select_tai, "area", "and", 10, 1000);
	union1 (select_tai, &union_tai);
	dilation_circle (union_tai, &dila_tai, 2);
	skeleton (dila_tai, &ske_tai);
	connection (ske_tai, &error_tai);
	select_shape (error_tai, &err, "outer_radius", "and", 10, 10000);

	count_obj(err, &error_number);

	if (error_number)
	{
		return;
	}


// //////////////////////////////////////////////////////////////////////////////black

		threshold (mean_tai, &white_tai, 0, 115);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &select_tai, "area", "and", 50, 1000);
		union1 (select_tai, &union_tai);
		dilation_circle (union_tai, &dila_tai, 1);
		skeleton (dila_tai, &ske_tai);
		connection (ske_tai, &error_tai);
		select_shape (error_tai, &err, "outer_radius", "and", 15, 10000);

		count_obj(err, &error_number);

				if (error_number)
				{
					return;
				}
/////////////////////////////////////////////////////////////////////////////////point


		threshold (mean_tai, &white_tai, 0, 80);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &err, "area", "and", 5, 1000);

		count_obj(err, &error_number);

		if (error_number)
				{
					return;
				}


////////////////////////////////////////////////////////////////////////////////press

		threshold (mean_tai, &white_tai, 140,255);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &err, "area", "and", 5, 1000);

		count_obj(err, &error_number);

				if (error_number)
				{
					return;
				}




		////////////////////////////////////////////////////////////a

		gen_circle(&c1, Tyy, Txx, TR-78);
		gen_circle(&c2, Tyy,Txx,TR-85);

		difference(c1, c2, &diff_taia);
		reduce_domain(image, diff_taia, &region_taia);
		mean_image (region_taia, &mean_tai, 2, 2);
		threshold(mean_tai, &white_tai, 90, 120);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &select_tai, "area", "and", 10, 1000);
		union1 (select_tai, &union_tai);
		dilation_circle (union_tai, &dila_tai, 1.5);
		skeleton (dila_tai, &ske_tai);
		connection (ske_tai, &error_tai);
		select_shape (error_tai, &err, "area", "and", 5, 10000);

		count_obj(err, &error_number);

		if (!error_number)
		{
			AfxMessageBox("good tai");
		}
