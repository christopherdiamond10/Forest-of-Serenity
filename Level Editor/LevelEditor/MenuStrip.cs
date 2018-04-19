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
        //================================
        //         New
        //================================
        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ResetEverything();
        }





        //================================
        //         Open File
        //================================
        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog.Title = "Select a File to Open";
            openFileDialog.FileName = "";
            openFileDialog.Filter = "Resource Files (*.xml;*.mp3;*.ogg;*.wav;*.jpg;*.png;*.gif;*.bmp)|*.xml;*.mp3;*.ogg;*.wav;*.jpg;*.png;*.gif;*.bmp";
            if (openFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string sExtension = System.IO.Path.GetExtension(openFileDialog.FileName);
                if (sExtension == ".xml")
                {
                    OpenXMLFile(openFileDialog.FileName);
                }
                else if (sExtension == ".mp3" || sExtension == ".ogg" || sExtension == ".wav")
                {
                    sAudioName = System.IO.Path.GetFileName(openFileDialog.FileName);
                    AudioInfo_TextBox.Text = sAudioName;
                }
                else
                {
                    sFullPathToImage = openFileDialog.FileName;
                    sBackgroundImageName = System.IO.Path.GetFileName(openFileDialog.FileName);
                    MapPanel.BackgroundImage = Image.FromFile(openFileDialog.FileName);
                }

                AddToRedoUndoList(); // Increment The List
            }
        }




        //================================
        //         Save A File
        //================================
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            bool bPlayerStartPositionExists = false; bool bLevelFinishingStarExists = false;

            foreach (List<LevelInfo> LevInfoList in lLevelInfoList)
            {
                foreach (LevelInfo LevInfo in LevInfoList)
                {
                    if (LevInfo.TextureName == "Player_Start")            { bPlayerStartPositionExists = true; }
                    else if (LevInfo.TextureName == "Star_LevelFinisher") { bLevelFinishingStarExists = true;  }
                }
            }
            if (!bPlayerStartPositionExists) { MessageBox.Show("You MUST have a Player Start position before you can save, check the events tab to find the option"); return; }
            if (!bLevelFinishingStarExists) { MessageBox.Show("You MUST have a Star_levelFinisher before you can save, check the events tab to find the option"); return; }
            


            string sWeatherEffectOne = null; string sWeatherEffectTwo = null;
            if (lWeatherEffectOne.Count() > 0) { sWeatherEffectOne = lWeatherEffectOne.ElementAt(0).Type; }
            if (lWeatherEffectTwo.Count() > 0) { sWeatherEffectTwo = lWeatherEffectTwo.ElementAt(0).Type; }


            oMapXML.WriteToXML(sFullPathToImage, sBackgroundImageName, sAudioName, (uint)AudioLoopStart_NumericUpDown.Value, (uint)AudioLoopEnd_NumericUpDown.Value,
                               sWeatherEffectOne, (uint)WeatherEffectOnePower_NumericUpDown.Value, sWeatherEffectTwo,
                               (uint)WeatherEffectTwoPower_NumericUpDown.Value, lLevelInfoList, (uint)oMapGrid.TileRowsValue, (uint)oMapGrid.TileColsValue );
        }



        //================================
        //         Quit
        //================================
        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }






        //================================
        //         Undo
        //================================
        private void undoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (lRedoUndoList.Count() > 0 && iCurrentElementInRedoUndoList > 0)
            {
                iCurrentElementInRedoUndoList--;
                PerformRedoUndo((int)iCurrentElementInRedoUndoList);
            }
        }



        //================================
        //         Redo
        //================================
        private void redoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (lRedoUndoList.Count() > iCurrentElementInRedoUndoList)
            {
                iCurrentElementInRedoUndoList++;
                PerformRedoUndo((int)iCurrentElementInRedoUndoList);
            }
        }








        //================================
        //         Open XML FIle
        //================================
        private void OpenXMLFile(string PathToFile)
        {
            string sWarning = "WARNING, by performing this action you will lose any unsaved progress, would you like to continue?";
            if (MessageBox.Show(sWarning, "Warning!", MessageBoxButtons.YesNo) != DialogResult.Yes) { return; }
            
            oMapXML.ReadFromXML(PathToFile);
            
            // Background Image
            sFullPathToImage = oMapXML.GetFullPathToBackgroundImage();
            sBackgroundImageName = oMapXML.GetBackgroundImageName();
            if (sFullPathToImage != "" && System.IO.File.Exists(sFullPathToImage)) { MapPanel.BackgroundImage = Image.FromFile(sFullPathToImage); }

            // Audio
            sAudioName = oMapXML.GetAudioName();
            AudioInfo_TextBox.Text = sAudioName;
            AudioLoopStart_NumericUpDown.Value = Convert.ToUInt64(oMapXML.GetAudioLoopStart());
            AudioLoopEnd_NumericUpDown.Value = Convert.ToUInt64(oMapXML.GetAudioLoopEnd());

            // Weather
            if      ( oMapXML.GetWeatherEffectOneType() == "None")    { WeatherEffect1_ComboBox.SelectedIndex = 0; }
            else if ( oMapXML.GetWeatherEffectOneType() == "Rain")    { WeatherEffect1_ComboBox.SelectedIndex = 1; }
            else if ( oMapXML.GetWeatherEffectOneType() == "Wind")    { WeatherEffect1_ComboBox.SelectedIndex = 2; }
            
            if      ( oMapXML.GetWeatherEffectTwoType() == "None")    { WeatherEffect2_ComboBox.SelectedIndex = 0; }
            else if ( oMapXML.GetWeatherEffectTwoType() == "Rain")    { WeatherEffect2_ComboBox.SelectedIndex = 1; }
            else if ( oMapXML.GetWeatherEffectTwoType() == "Wind")    { WeatherEffect2_ComboBox.SelectedIndex = 2; }

            WeatherEffectOnePower_NumericUpDown.Value = Convert.ToInt32(oMapXML.GetWeatherEffectOnePower());
            WeatherEffectTwoPower_NumericUpDown.Value = Convert.ToInt32(oMapXML.GetWeatherEffectTwoPower());
            MakeWeatherEffect(1); MakeWeatherEffect(2);

            // Rows and Cols
            oMapGrid.TileRowsValue = Convert.ToInt32(oMapXML.GetTileRows());
            oMapGrid.TileColsValue = Convert.ToInt32(oMapXML.GetTileCols());

            // List
            lLevelInfoList.Clear();
            foreach (List<LevelInfo> LevInfoList in oMapXML.GetLevelList())
            {
                List<LevelInfo> LevelInfoList = new List<LevelInfo>();
                foreach (LevelInfo LevInfo in LevInfoList)
                {
                    LevelInfo Levelinfo = new LevelInfo();
                    Levelinfo.X = LevInfo.X; Levelinfo.Y = LevInfo.Y; Levelinfo.W = LevInfo.W; Levelinfo.H = LevInfo.H;
                    Levelinfo.TextureName = LevInfo.TextureName;
                    
                    // Get The Texture
                    foreach (TexturesInfo TextInfo in lTexturesList)
                    {
                        if (TextInfo.TextureName == Levelinfo.TextureName)
                        {
                            Levelinfo.Texture = TextInfo.Texture;
                            break;
                        }
                    }
                    LevelInfoList.Add(Levelinfo);
                }
                lLevelInfoList.Add(LevelInfoList);
            }

            // Set XML To Null
            oMapXML.SetClassXmlToNull();

            MapPanel.Invalidate();
        }


        private void PerformRedoUndo(int RedoUndoElement)
        {
            // Make sure we are within range
            if ((RedoUndoElement >= 0) && (lRedoUndoList.Count() > RedoUndoElement))
            {
                RedoUndoInfo RedoUndo = lRedoUndoList.ElementAt(RedoUndoElement);
                ///////////////////////////////////////////////////////////////////////////////////
                // Get Image Info
                sBackgroundImageName = RedoUndo.BackgroundImageName;
                sFullPathToImage = RedoUndo.FullPathToImage;
                if (sFullPathToImage != null && System.IO.File.Exists(sFullPathToImage)) { MapPanel.BackgroundImage = Image.FromFile(sFullPathToImage); } else { MapPanel.BackgroundImage = null; }
                ///////////////////////////////////////////////////////////////////////////////////
                // Get Audio Info
                sAudioName = RedoUndo.AudioName;
                AudioInfo_TextBox.Text = RedoUndo.AudioInfoTextBoxText;
                AudioLoopStart_NumericUpDown.Value = RedoUndo.AudioLoopStart_NumericUpDownValue;
                AudioLoopEnd_NumericUpDown.Value = RedoUndo.AudioLoopEnd_NumericUpDownValue;
                ///////////////////////////////////////////////////////////////////////////////////
                // Get Weather Info
                lWeatherEffectOne = RedoUndo.lWeatherEffectOne;
                lWeatherEffectTwo = RedoUndo.lWeatherEffectTwo;

                WeatherEffect1_ComboBox.SelectedIndex = RedoUndo.WeatherEffect1_ComboBoxSelectedIndex;
                WeatherEffect2_ComboBox.SelectedIndex = RedoUndo.WeatherEffect2_ComboBoxSelectedIndex;
                WeatherEffectOnePower_NumericUpDown.Value = RedoUndo.WeatherEffectOnePower_NumericUpDownValue;
                WeatherEffectTwoPower_NumericUpDown.Value = RedoUndo.WeatherEffectTwoPower_NumericUpDownValue;
                ///////////////////////////////////////////////////////////////////////////////////
                // Get Numeric Up/Downs Info
                TileRows_NumericUpDown.Value = oMapGrid.TileRowsValue = RedoUndo.TileRows_NumericUpDownValue;
                TileCols_NumericUpDown.Value = oMapGrid.TileColsValue = RedoUndo.TileCols_NumericUpDownValue;
                ///////////////////////////////////////////////////////////////////////////////////
                // Get Level Data
                lLevelInfoList = RedoUndo.lLevelDataList;

                // Invalidate the Map
                MapPanel.Invalidate();
            }
        }
    }
}
