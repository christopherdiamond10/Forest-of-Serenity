using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace LevelEditor
{
    public partial class Forest_of_Serenity_LevelEditor : Form
    {
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        //              New Instances
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
        MapGrid oMapGrid                        = new MapGrid();
        Pen_and_Brush oPen_and_Brush            = new Pen_and_Brush();
        MousePos oMousePos                      = new MousePos();
        MapXML oMapXML                          = new MapXML();

        uint iActionState                       = (uint)ActionState.AddLevelTile;
        uint iTabState                          = (uint)TabState.Platforms;
        uint iDataState                         = (uint)DataState.Platform1A;
        uint iCurrentElementInRedoUndoList      = 0;

        List<RedoUndoInfo> lRedoUndoList        = new List<RedoUndoInfo>();
        List<List<LevelInfo>> lLevelInfoList    = new List<List<LevelInfo>>();
        List<TexturesInfo> lTexturesList        = new List<TexturesInfo>();

        List<WeatherInfo> lWeatherEffectOne     = new List<WeatherInfo>();
        List<WeatherInfo> lWeatherEffectTwo     = new List<WeatherInfo>();


        string sAudioName                       = null;
        string sBackgroundImageName             = null;
        string sFullPathToImage                 = null;



        //=====================================
        //  Constructor
        //=====================================
        public Forest_of_Serenity_LevelEditor()
        {
            InitializeComponent();

            // Set Colours
            MapPanel.BackColor = Color.Brown;
            this.BackColor = Color.Cyan;
            IsMdiContainer = true;

            // Set Image Layout
            MapPanel.BackgroundImageLayout = ImageLayout.None;

            // Set Graphics
            oPen_and_Brush.ClassGraphics = MapPanel.CreateGraphics();

            // Set Tiles
            oMapGrid.TileRowsValue = (int)TileRows_NumericUpDown.Value;
            oMapGrid.TileColsValue = (int)TileCols_NumericUpDown.Value;

            UpSizeLevelInfoList();

            // Setup All Textures
            SetAllTextures();

            // Increment The List
            AddToRedoUndoList(); 
        }



        //=====================================
        //  Setup All Textures
        //=====================================
        private void SetAllTextures()
        {
            iTabState = (uint)TabState.Platforms;
            for (iDataState = (uint)DataState.Platform1A; iDataState <= (uint)DataState.Platform8C; iDataState++)           { GetImageforCurrentState(); }
            iTabState = (uint)TabState.Walls;
            for (iDataState = (uint)DataState.Platform1WallA; iDataState <= (uint)DataState.Platform4WallC; iDataState++)   { GetImageforCurrentState(); }
            iTabState = (uint)TabState.Others;
            for (iDataState = (uint)DataState.Flower; iDataState <= (uint)DataState.Shading1A; iDataState++)                { GetImageforCurrentState(); }
            iTabState = (uint)TabState.Events;
            for (iDataState = (uint)DataState.PlayerStart; iDataState <= (uint)DataState.Purple_Crystal; iDataState++)      { GetImageforCurrentState(); }
            iDataState = (uint)DataState.Platform1A;  iTabState = (uint)TabState.Platforms;
        }








        //=====================================
        //  Reset Everything
        //=====================================
        private void ResetEverything()
        {
            if (!ClearLevelInfoArray()) { return; }
            sAudioName              = null;
            sBackgroundImageName    = null;
            sFullPathToImage        = null;

            MapPanel.BackgroundImage = null;

            AudioInfo_TextBox.Text = "";
            AudioLoopStart_NumericUpDown.Value = 0;
            AudioLoopEnd_NumericUpDown.Value = 0;


            lWeatherEffectOne.Clear();
            lWeatherEffectTwo.Clear();

            WeatherEffect1_ComboBox.SelectedIndex = 0;
            WeatherEffect2_ComboBox.SelectedIndex = 0;
            WeatherEffectOnePower_NumericUpDown.Value = 1;
            WeatherEffectTwoPower_NumericUpDown.Value = 1;

            TileRows_NumericUpDown.Value = oMapGrid.TileRowsValue = 24;
            TileCols_NumericUpDown.Value = oMapGrid.TileColsValue = 32;
        }





        //=====================================
        //  Add to Redo/Undo List
        //=====================================
        private void AddToRedoUndoList()
        {
            // Clear Any Redo Elements if No Longer needed
            while (lRedoUndoList.Count() > iCurrentElementInRedoUndoList) { lRedoUndoList.RemoveAt(lRedoUndoList.Count() - 1); }

            // Add an UndoRedo Element to the List
            RedoUndoInfo RedoUndoinfo = new RedoUndoInfo();
            //////////////////////////////////////////////////////////////////////////////////////////////////////////
            RedoUndoinfo.BackgroundImageName                = sBackgroundImageName;
            RedoUndoinfo.FullPathToImage                    = sFullPathToImage;
            //////////////////////////////////////////////////////////////////////////////////////////////////////////
            RedoUndoinfo.AudioName                          = sAudioName;
            RedoUndoinfo.AudioInfoTextBoxText               = AudioInfo_TextBox.Text;
            RedoUndoinfo.AudioLoopStart_NumericUpDownValue  = (int)AudioLoopStart_NumericUpDown.Value;
            RedoUndoinfo.AudioLoopEnd_NumericUpDownValue    = (int)AudioLoopEnd_NumericUpDown.Value;
            // Add Weather ///////////////////////////////////////////////////////////////////////////////////////////
            RedoUndoinfo.lWeatherEffectOne = new List<WeatherInfo>();
            foreach (WeatherInfo Weather in lWeatherEffectOne)
            {
                WeatherInfo Weath; Weath.H = Weather.H; Weath.Texture = Weather.Texture; Weath.Type = Weather.Type;
                Weath.W = Weather.W; Weath.X = Weather.X; Weath.Y = Weather.Y;
                RedoUndoinfo.lWeatherEffectOne.Add(Weath);
            }
            RedoUndoinfo.lWeatherEffectTwo = new List<WeatherInfo>();
            foreach (WeatherInfo Weather in lWeatherEffectTwo)
            {
                WeatherInfo Weath; Weath.H = Weather.H; Weath.Texture = Weather.Texture; Weath.Type = Weather.Type;
                Weath.W = Weather.W; Weath.X = Weather.X; Weath.Y = Weather.Y;
                RedoUndoinfo.lWeatherEffectTwo.Add(Weath);
            }
            RedoUndoinfo.WeatherEffect1_ComboBoxSelectedIndex = WeatherEffect1_ComboBox.SelectedIndex;
            RedoUndoinfo.WeatherEffect2_ComboBoxSelectedIndex = WeatherEffect2_ComboBox.SelectedIndex;
            RedoUndoinfo.WeatherEffectOnePower_NumericUpDownValue = (int)WeatherEffectOnePower_NumericUpDown.Value;
            RedoUndoinfo.WeatherEffectTwoPower_NumericUpDownValue = (int)WeatherEffectTwoPower_NumericUpDown.Value;
            //////////////////////////////////////////////////////////////////////////////////////////////////////////
            RedoUndoinfo.TileRows_NumericUpDownValue = (int)TileRows_NumericUpDown.Value;
            RedoUndoinfo.TileCols_NumericUpDownValue = (int)TileCols_NumericUpDown.Value;
            //////////////////////////////////////////////////////////////////////////////////////////////////////////
            RedoUndoinfo.lLevelDataList = new List<List<LevelInfo>>();
            foreach (List<LevelInfo> LevelInfoList in lLevelInfoList)
            {
                List<LevelInfo> LevInfoList = new List<LevelInfo>();
                foreach (LevelInfo LevInfo in LevelInfoList)
                {
                    LevelInfo Levelinfo = new LevelInfo();
                    Levelinfo.X = LevInfo.X; Levelinfo.Y = LevInfo.Y; Levelinfo.W = LevInfo.W; Levelinfo.H = LevInfo.H;
                    Levelinfo.TextureName = LevInfo.TextureName; Levelinfo.Texture = LevInfo.Texture;
                    LevInfoList.Add(Levelinfo);
                }
                RedoUndoinfo.lLevelDataList.Add(LevInfoList);
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////
            lRedoUndoList.Add(RedoUndoinfo); 
            iCurrentElementInRedoUndoList++;
        }












        //=====================================
        //  Tile Control Numeric UpDown
        //=====================================
        private void TileRows_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            oMapGrid.TileRowsValue = (int)TileRows_NumericUpDown.Value;
            UpSizeLevelInfoList();
            MapPanel.Invalidate();
            AddToRedoUndoList(); // Increment The List
        }


        private void TileCols_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            oMapGrid.TileColsValue = (int)TileCols_NumericUpDown.Value;
            UpSizeLevelInfoList();
            MapPanel.Invalidate();
            AddToRedoUndoList(); // Increment The List
        }




        //=====================================
        //      UpSize Level Info List
        //=====================================
        private void UpSizeLevelInfoList()
        {

            ///////////////// ADD TO THE LIST /////////////////
            // If there are not as many rows in the Level List as there are in the Value Box
            while (lLevelInfoList.Count() < oMapGrid.TileRowsValue)
            {
                // Make Each Element in the list Move down a tile
                foreach (List<LevelInfo> LevInfoList in lLevelInfoList)
                {
                    foreach (LevelInfo LevInfo in LevInfoList)
                    {
                        LevInfo.Y += (uint)oMapGrid.TileSizeValue;
                    }
                }

                // Now Add a new row at the top of the list (the next loop will deal with the assignments)
                List<LevelInfo> LevelData = new List<LevelInfo>();
                lLevelInfoList.Insert(0, LevelData);
            }



            for (int i = 0; i < lLevelInfoList.Count(); i++)
            {
                while (lLevelInfoList.ElementAt(i).Count() < oMapGrid.TileColsValue)
                {
                    LevelInfo LevInfo = new LevelInfo();
                    LevInfo.X = ((uint)lLevelInfoList.ElementAt(i).Count() * (uint)oMapGrid.TileSizeValue); LevInfo.W = (uint)oMapGrid.TileSizeValue;
                    LevInfo.Y = ((uint)i * (uint)oMapGrid.TileSizeValue); LevInfo.H = (uint)oMapGrid.TileSizeValue;
                    lLevelInfoList.ElementAt(i).Add(LevInfo);
                }
            }


            ///////////////// REMOVE FROM THE LIST /////////////////
            // Removing Rows
            while (lLevelInfoList.Count() > oMapGrid.TileRowsValue)
            {
                // Remove UpperMost Row
                lLevelInfoList.RemoveAt(0);

                // Bring all remaining LevelData Positions up one tile
                foreach (List<LevelInfo> LevInfoList in lLevelInfoList)
                {
                    foreach (LevelInfo LevInfo in LevInfoList)
                    {
                        LevInfo.Y -= (uint)oMapGrid.TileSizeValue;
                    }
                }
            }

            // Removing Columns
            foreach (List<LevelInfo> LevInfoList in lLevelInfoList)
            {
                while (LevInfoList.Count() > oMapGrid.TileColsValue)
                {
                    LevInfoList.RemoveAt(LevInfoList.Count() - 1);
                }
            }
        }



        //=====================================
        //      Clear Leve Array
        //=====================================
        private bool ClearLevelInfoArray()
        {
            string sWarning = "WARNING, by performing this action you will lose any unsaved progress, would you like to continue?";
            if (MessageBox.Show(sWarning, "Warning!", MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                foreach (List<LevelInfo> LevInfoList in lLevelInfoList)
                {
                    foreach (LevelInfo LevInfo in LevInfoList)
                    {
                        LevInfo.Texture = null; LevInfo.TextureName = null;
                    }
                }
                return true;
            }
            return false;
        }




        //=====================================
        //  Tab Control Selected Index Changed
        //=====================================
        private void ButtonSelection_TabControl_SelectedIndexChanged(object sender, EventArgs e)
        {
            if      (ButtonSelection_TabControl.SelectedIndex == 0) { iTabState = (uint)TabState.Platforms;     iDataState = (uint)DataState.Platform1A; }
            else if (ButtonSelection_TabControl.SelectedIndex == 1) { iTabState = (uint)TabState.Walls;         iDataState = (uint)DataState.Platform1WallA; }
            else if (ButtonSelection_TabControl.SelectedIndex == 2) { iTabState = (uint)TabState.Others;        iDataState = (uint)DataState.Flower; }
            else if (ButtonSelection_TabControl.SelectedIndex == 3) { iTabState = (uint)TabState.Events;        iDataState = (uint)DataState.Platform1A; }
        }



        //=====================================
        //  Make Weather Effect
        //=====================================
        private void MakeWeatherEffect(uint iWhichList)
        {
            uint AmountOfWeather = 0;
            WeatherInfo Weather = new WeatherInfo();
            Random RandomNumber = new Random();

            Weather.W = (uint)oMapGrid.TileSizeValue; Weather.H = (uint)oMapGrid.TileSizeValue;



            if( iWhichList == 1 ) 
            {
                if (WeatherEffect1_ComboBox.SelectedIndex == 1) // Rain
                {
                    AmountOfWeather = 10 * (uint)WeatherEffectOnePower_NumericUpDown.Value;
                    Weather.Texture = null; 
                    Weather.Type = "Rain";
                }
                else if (WeatherEffect1_ComboBox.SelectedIndex == 2) // Wind
                {
                    AmountOfWeather = (uint)WeatherEffectOnePower_NumericUpDown.Value;
                    Weather.Texture = Image.FromFile("./Images/Wind_Texture.png"); 
                    Weather.Type = "Wind";
                }


                while(lWeatherEffectOne.Count() < AmountOfWeather) 
                {
                    Weather.X = (uint)RandomNumber.Next((int)Weather.W, 1024);
                    Weather.Y = (uint)RandomNumber.Next(0, 768);
                    lWeatherEffectOne.Add(Weather);
                }
                
                if (lWeatherEffectOne.Count() > AmountOfWeather)
                {
                    lWeatherEffectOne.Clear();

                    // Recursive Function
                    MakeWeatherEffect(iWhichList);
                }
            }

            else if( iWhichList == 2 )
            {
                if (WeatherEffect2_ComboBox.SelectedIndex == 1) // Rain
                {
                    AmountOfWeather = 10 * (uint)WeatherEffectTwoPower_NumericUpDown.Value;
                    Weather.Texture = null;
                    Weather.Type = "Rain";
                }
                else if (WeatherEffect2_ComboBox.SelectedIndex == 2) // Wind
                {
                    AmountOfWeather = (uint)WeatherEffectTwoPower_NumericUpDown.Value;
                    Weather.Texture = Image.FromFile("./Images/Wind_Texture.png");
                    Weather.Type = "Wind";
                }


                while (lWeatherEffectTwo.Count() < AmountOfWeather)
                {
                    Weather.X = (uint)RandomNumber.Next((int)Weather.W, 1024);
                    Weather.Y = (uint)RandomNumber.Next(0, 768);
                    lWeatherEffectTwo.Add(Weather);
                }

                if (lWeatherEffectTwo.Count() > AmountOfWeather)
                {
                    lWeatherEffectTwo.Clear();

                    // Recursive Function
                    MakeWeatherEffect(iWhichList);
                }
            }
        }


        //=====================================
        //  Weather Effect Controls
        //=====================================
        private void WeatherEffect1_ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            lWeatherEffectOne.Clear();
            MakeWeatherEffect(1);
            MapPanel.Invalidate();
            AddToRedoUndoList(); // Increment The List
        }

        private void WeatherEffectOnePower_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            MakeWeatherEffect(1);
            MapPanel.Invalidate();
            AddToRedoUndoList(); // Increment The List
        }

        private void WeatherEffect2_ComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            lWeatherEffectTwo.Clear();
            MakeWeatherEffect(2);
            MapPanel.Invalidate();
            AddToRedoUndoList(); // Increment The List
        }

        private void WeatherEffectTwoPower_NumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            MakeWeatherEffect(2);
            MapPanel.Invalidate();
            AddToRedoUndoList(); // Increment The List
        }








        //=====================================
        //  Process Command Keys ~ This is what makes crtl-Z pull off an undo
        //=====================================
        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            // if it is a hotkey, return true; otherwise, return false
            switch (keyData)
            {
                case Keys.Control | Keys.Z:
                    {
                        if (lRedoUndoList.Count() > 0 && iCurrentElementInRedoUndoList > 0)
                        {
                            iCurrentElementInRedoUndoList--;
                            PerformRedoUndo((int)iCurrentElementInRedoUndoList);
                        }
                        return true;
                    }

                case Keys.Control | Keys.Y:
                    {
                        if (lRedoUndoList.Count() > iCurrentElementInRedoUndoList + 1)
                        {
                            iCurrentElementInRedoUndoList++;
                            PerformRedoUndo((int)iCurrentElementInRedoUndoList);
                        }
                        return true;
                    }
                    
                default:
                    break;
            }
            return false;
        }  
    }
}
