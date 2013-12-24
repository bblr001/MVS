================================================================================
    MICROSOFT 基础类库: AOIEDITHelp 项目概述
===============================================================================

应用程序向导已为您创建此 AOIEDITHelp 应用程序。此应用程序不仅演示使用 Microsoft 基础类的基本知识，而且可作为编写应用程序的起点。

此文件包含组成 AOIEDITHelp 应用程序的各个文件的内容摘要。

AOIEDITHelp.vcproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件。
    它包含有关生成文件的 Visual C++ 版本的信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

AOIEDITHelp.h
    这是应用程序的主要头文件。它包括其他项目特定的头文件(包括 Resource.h)，并声明 CAOIEDITHelpApp 应用程序类。

AOIEDITHelp.cpp
    这是包含应用程序类 CAOIEDITHelpApp 的主要应用程序源文件。

AOIEDITHelp.rc
    这是程序使用的所有 Microsoft Windows 资源的列表。它包括 RES 子目录中存储的图标、位图和光标。此文件可以直接在 Microsoft Visual C++ 中进行编辑。项目资源位于 2052 中。

res\AOIEDITHelp.ico
    这是用作应用程序图标的图标文件。此图标包括在主要资源文件 AOIEDITHelp.rc 中。

res\AOIEDITHelp.rc2
    此文件包含不是由 Microsoft Visual C++ 编辑的资源。您应该将不可由资源编辑器编辑的所有资源放在此文件中。

AOIEDITHelp.reg
    这是一个示例 .reg 文件，它显示了框架将为您设置的注册设置的种类。可以将它用作
    将与您的应用程序一起使用的 .reg 文件，或者索性将它删除，而采用默认的 RegisterShellFileTypes 注册。


/////////////////////////////////////////////////////////////////////////////

对于主框架窗口:
    项目包含标准 MFC 界面。

MainFrm.h, MainFrm.cpp
    这些文件包含框架类 CMainFrame，该类派生自
    CFrameWnd 并控制所有 SDI 框架功能。

res\Toolbar.bmp
    此位图文件用于为工具栏创建平铺图像。
    初始工具栏和状态栏是在 CMainFrame 类中构造的。使用资源编辑器编辑此工具栏位图，并更新 AOIEDITHelp.rc 中的 IDR_MAINFRAME TOOLBAR 数组以添加工具栏按钮。
/////////////////////////////////////////////////////////////////////////////

应用程序向导创建一个文档类型和一个视图:

AOIEDITHelpDoc.h，AOIEDITHelpDoc.cpp - 文档
    这些文件包含 CAOIEDITHelpDoc 类。编辑这些文件可以添加特殊文档数据并可实现文件保存和加载(通过 CAOIEDITHelpDoc::Serialize)。
    文档将具有下列字符串:
        文件扩展名:Insp
        文件类型 ID:AOIEDITHelp.Document
        主框架标题:AOIEDITHelp
        文档类型名称:AOIEDITHelp
        筛选器名:AOIEDITHelp Files (*.Insp)
        文件的新简称:AOIEDITHelp
        文件类型全名:AOIEDITHelp.Document

AOIEDITHelpView.h，AOIEDITHelpView.cpp - 文档的视图
    这些文件包含 CAOIEDITHelpView 类。
    CAOIEDITHelpView 对象用于查看 CAOIEDITHelpDoc 对象。




/////////////////////////////////////////////////////////////////////////////

帮助支持：

hlp\AOIEDITHelp.hhp
    此文件是帮助项目文件。它包含将帮助文件编译为 .chm 文件所需的数据。

hlp\AOIEDITHelp.hhc
    此文件列出帮助项目的内容。

hlp\AOIEDITHelp.hhk
    此文件包含帮助主题的索引。

hlp\afxcore.htm
    此文件包含标准 MFC 命令和屏幕对象的标准帮助主题。将您自己的帮助主题添加到此文件中。

makehtmlhelp.bat
    此文件由生成系统用来编译帮助文件。

hlp\Images\*.gif
    这些是 Microsoft 基础类库标准命令的标准帮助文件主题所需的位图文件。


/////////////////////////////////////////////////////////////////////////////

其他功能:

拆分窗口
    应用程序向导已为应用程序文档添加了拆分窗口支持。

/////////////////////////////////////////////////////////////////////////////

其他标准文件:

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 AOIEDITHelp.pch 的预编译头(PCH)文件和名为 StdAfx.obj 的预编译类型文件。

Resource.h
    这是标准头文件，它定义新资源 ID。
    Microsoft Visual C++ 将读取并更新此文件。

/////////////////////////////////////////////////////////////////////////////

其他注释:

应用程序向导使用“TODO:”指示应添加或自定义的源代码部分。

如果应用程序在共享 DLL 中使用 MFC,则将需要重新发布 MFC DLL。如果应用程序所用与操作系统的区域设置不同，则也将必须重新发布对应的本地化资源 MFC90XXX.DLL。
有关这两个主题的详细信息，请参阅 MSDN 文档中有关重新发布 Visual C++ 应用程序的部分。

/////////////////////////////////////////////////////////////////////////////