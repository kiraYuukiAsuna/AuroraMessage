﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AuroraMessageClientGui;

namespace AuroraMessageClientGui
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (userID.Text != "")
            {
                if (userPassword.Password != "")
                {

                }
                else
                {
                    MessageBox.Show("密码不能为空！", "错误！");
                }
            }
            else
            {
                MessageBox.Show("账号不能为空！","错误！");
            }
        }
    }
}
