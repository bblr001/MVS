//input: int Thred_jiao=350, Thred_jiao_inter=500, Thred_jiao_outer=800; Txx, Tyy, TR;
//output: 	Hlong TxxError_jiao, TyyError_jiao; bool Jiaogood;






    int Thred_error_jiao=0;
	Hobject PolarTransImage_jiao, ImageEmphasize_jiao, ImageSub_jiao, ImageInvert_jiao;
	double tem_jiao, teml[160];
	int i, j, k;
	Jiaogood=0;
	polar_trans_image_ext (image, &PolarTransImage_jiao, Tyy, Txx, 0, 6.74, TR-18, TR-7, 640, 12, "bilinear");
	emphasize(PolarTransImage_jiao, &ImageEmphasize_jiao, 5, 5, 3);
	invert_image(PolarTransImage_jiao, &ImageInvert_jiao);
	sub_image(ImageInvert_jiao, ImageEmphasize_jiao, &ImageSub_jiao, 1, 1);
	for (i=0; i<3; i++)
	{
		teml[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=4; k<8; k++)
			{
				get_grayval(ImageSub_jiao, k, j, &tem_jiao);
				teml[i]=teml[i]+tem_jiao;	
			}
		}
	}

	for (i=3; i<155; i++)
	{
		teml[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=4; k<8; k++)
			{
				get_grayval(ImageSub_jiao, k, j, &tem_jiao);
				teml[i]=teml[i]+tem_jiao;	
			}	
		}
		if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_jiao)
		{
			Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
			TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
			TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
		}
	}
	if (Thred_error_jiao<=Thred_jiao)
	{
		for (i=0; i<3; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=8; k<12; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}
			}
		}
		
		for (i=3; i<155; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=8; k<12; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}	
			}
			if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_jiao_outer)
			{
				Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
				TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
				TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
			}
		}
	}
	
	if (Thred_error_jiao<=Thred_jiao_outer&&Thred_error_jiao<=Thred_jiao)
	{
		for (i=0; i<3; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<4; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}
			}
		}
		
		for (i=3; i<155; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<4; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}	
			}
			if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_jiao_inter)
			{
				Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
				TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
				TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
			}
		}	
		
	}


	if (Thred_error_jiao<=Thred_jiao_inter&&Thred_error_jiao<=Thred_jiao_outer&&Thred_error_jiao<=Thred_jiao)
	{
		Jiaogood=1;
	}


	