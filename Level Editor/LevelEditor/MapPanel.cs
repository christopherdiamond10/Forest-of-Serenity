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
        //=====================================
        //      MapPanel Paint
        //=====================================
        private void MapPanel_Paint(object sender, PaintEventArgs e)
        {
            DrawLevelData();
            DrawWeather();
            DrawMapGrid();
        }




        //=====================================
        //      MapPanel MouseClick
        //=====================================
        private void MapPanel_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button.ToString() == "Left")
            {
                if (iActionState == (uint)ActionState.AddLevelTile)
                {
                    AddLevelDataElement();
                }
                else
                {
                    RemoveLevelDataElement();
                }
            }

            else if (e.Button.ToString() == "Right")
            {
                RemoveLevelDataElement();
            }
        }
        //=====================================
        //      MapPanel MouseMove
        //=====================================
        private void MapPanel_MouseMove(object sender, MouseEventArgs e)
        {
            oMousePos.X = e.X; oMousePos.Y = e.Y;
            MouseCoords_TextBox.Text = "X = " + e.X.ToString() + ", Y = " + e.Y.ToString();
        }
        //=====================================
        //      MapPanel ScrollBoxMoved
        //=====================================
        private void MapPanel_ScrollBoxMoved(object sender, ScrollEventArgs e)
        {
            //MessageBox.Show(e.OldValue.ToString());
            //MessageBox.Show(e.NewValue.ToString());
            //MessageBox.Show(e.ScrollOrientation.ToString());
            //MessageBox.Show(e.Type.ToString());
        }




        //=====================================
        //      Add Level Data Element
        //=====================================
        private void AddLevelDataElement()
        {
            Image TextureImage = GetImageforCurrentState(); string Name = GetNameforCurrentTexture();   // Get Texture and Name
            if (TextureImage == null || Name == null) { return; }                                       // Return if either of them are null
            int[] iCurrentElement = GetCurrentPointInLevelData();                                       // Get the Current Element in which the mouse is positioned in


            ///////////////////////////////////////////////////////////
            // There can only be one Player Start Location and Level Finishing Stars
            if (Name == "Player_Start" || Name == "Star_LevelFinisher")
            {
                foreach (List<LevelInfo> LevInfoList in lLevelInfoList)
                {
                    foreach (LevelInfo LevInfo in LevInfoList)
                    {
                        if (LevInfo.TextureName == Name)
                        {
                            LevInfo.Texture = null;
                            LevInfo.TextureName = null;
                            DrawRectOverTexture(LevInfo.X, LevInfo.Y);
                        }
                    }
                }
            }
            ///////////////////////////////////////////////////////////


            // Check to make sure we are within range, the list doesn't always keep up with you if you click random tiles very quickly, so this safety check is needed
            if ((lLevelInfoList.Count > iCurrentElement[0]) && lLevelInfoList.ElementAt(iCurrentElement[0]).Count() > iCurrentElement[1])
            {

                // Add them to the element in the list
                lLevelInfoList.ElementAt(iCurrentElement[0]).ElementAt(iCurrentElement[1]).Texture = TextureImage;
                lLevelInfoList.ElementAt(iCurrentElement[0]).ElementAt(iCurrentElement[1]).TextureName = Name;

                DrawLevelDataElement(lLevelInfoList.ElementAt(iCurrentElement[0]).ElementAt(iCurrentElement[1]));
            }

            AddToRedoUndoList(); // Increment The List
        }

        //=====================================
        //      Remove Level Data Element
        //=====================================
        private void RemoveLevelDataElement()
        {
            int[] iCurrentElement = GetCurrentPointInLevelData();

            if ((lLevelInfoList.Count > iCurrentElement[0]) && lLevelInfoList.ElementAt(iCurrentElement[0]).Count() > iCurrentElement[1])
            {
                lLevelInfoList.ElementAt(iCurrentElement[0]).ElementAt(iCurrentElement[1]).Texture = null;
                lLevelInfoList.ElementAt(iCurrentElement[0]).ElementAt(iCurrentElement[1]).TextureName = null;

                // Hide the Texture behind a same colour as background background Rectangle
                DrawRectOverTexture(lLevelInfoList.ElementAt(iCurrentElement[0]).ElementAt(iCurrentElement[1]).X, lLevelInfoList.ElementAt(iCurrentElement[0]).ElementAt(iCurrentElement[1]).Y);
            }
            
            AddToRedoUndoList(); // Increment The List
        }




        //=====================================
        //  Draw Rect Over Texture ~ Removal
        //=====================================
        private void DrawRectOverTexture( uint X, uint Y )
        {
            // Just draw a rectangle of the same colour over the texture that needs to be "removed", the map panel doesn't need to invalidate for this one task
            System.Drawing.Brush TmpBrush = new SolidBrush( MapPanel.BackColor );
            Rectangle Rect = new Rectangle((int)X, (int)Y, (int)oMapGrid.TileSizeValue, (int)oMapGrid.TileSizeValue);
            oPen_and_Brush.ClassGraphics.FillRectangle(TmpBrush, Rect);
            TmpBrush.Dispose();
        }
        //=====================================
        //      Draw Map Grid
        //=====================================
        private void DrawMapGrid()
        {
            for (int Row = 0; Row <= oMapGrid.TileRowsValue; Row++)
            {
                oPen_and_Brush.ClassGraphics.DrawLine(oPen_and_Brush.ClassPen, 0, Row * oMapGrid.TileSizeValue, oMapGrid.TileColsValue * oMapGrid.TileSizeValue, Row * oMapGrid.TileSizeValue);
            }
            for (int Col = 0; Col <= oMapGrid.TileColsValue; Col++)
            {
                oPen_and_Brush.ClassGraphics.DrawLine(oPen_and_Brush.ClassPen, Col * oMapGrid.TileSizeValue, 0, Col * oMapGrid.TileSizeValue, oMapGrid.TileRowsValue * oMapGrid.TileSizeValue);
            }
        }





        //=====================================
        //      Draw Level Data
        //=====================================
        private void DrawLevelData()
        {
            foreach (List<LevelInfo> LevInfoList in lLevelInfoList)
            {
                foreach (LevelInfo LevInfo in LevInfoList)
                {
                    if (LevInfo.Texture != null)
                    {
                        DrawLevelDataElement(LevInfo);
                    }
                }
            }
        }


        //=====================================
        //      Draw Weather
        //=====================================
        private void DrawWeather()
        {
            System.Drawing.Pen TmpPen = new Pen(Color.WhiteSmoke);

            foreach( WeatherInfo Weather in lWeatherEffectOne )
            {
                if(Weather.Type == "Rain")
                {

                    oPen_and_Brush.ClassGraphics.DrawLine(TmpPen, (int)Weather.X, (int)Weather.Y, (int)(Weather.X - Weather.W), (int)(Weather.Y + Weather.H));
                }
                else if( Weather.Type == "Wind")
                {
                    oPen_and_Brush.ClassGraphics.DrawImage( Weather.Texture, (int)Weather.X, (int)Weather.Y);
                }
            }
            foreach (WeatherInfo Weather in lWeatherEffectTwo)
            {
                if(Weather.Type == "Rain")
                {
                    oPen_and_Brush.ClassGraphics.DrawLine(TmpPen, (int)Weather.X, (int)Weather.Y, (int)(Weather.X - Weather.W), (int)(Weather.Y + Weather.H));
                }
                else if( Weather.Type == "Wind")
                {
                    oPen_and_Brush.ClassGraphics.DrawImage( Weather.Texture, (int)Weather.X, (int)Weather.Y);
                }
            }

            TmpPen.Dispose();
        }


        //=====================================
        //      Draw Level Data Element
        //=====================================
        private void DrawLevelDataElement(LevelInfo LevInfo)
        {
            oPen_and_Brush.ClassGraphics.DrawImage(LevInfo.Texture, (float)LevInfo.X, (float)LevInfo.Y, (float)LevInfo.W, (float)LevInfo.H);
        }








        //=====================================
        //   Get Current Point In Level Data
        //=====================================
        private int[] GetCurrentPointInLevelData()
        {
            int iMasterListElement = 0;
            int iSlaveListElement = 0;

            for (; iMasterListElement < lLevelInfoList.Count(); iMasterListElement++)
            {
                if ((oMousePos.Y > (iMasterListElement * oMapGrid.TileSizeValue)) && (oMousePos.Y < ((iMasterListElement + 1) * oMapGrid.TileSizeValue)))
                {
                    for (; iSlaveListElement < lLevelInfoList.ElementAt(iMasterListElement).Count(); iSlaveListElement++)
                    {
                        if ((oMousePos.X > (iSlaveListElement * oMapGrid.TileSizeValue)) && (oMousePos.X < ((iSlaveListElement + 1) * oMapGrid.TileSizeValue)))
                        {
                            break;
                        }
                    }
                    break;
                }
            }

            int[] ReturnArray = new int[2];
            ReturnArray[0] = iMasterListElement;
            ReturnArray[1] = iSlaveListElement;
            return ReturnArray;
        }







        //=====================================
        //     Get Images for Current State
        //=====================================
        private Image GetImageforCurrentState()
        {
            string sPathToImage = "./Images";
            ////////////////////////////////////////////////////
            if      (iTabState == (uint)TabState.Platforms) { sPathToImage += "/Platforms/"; }
            else if (iTabState == (uint)TabState.Walls)     { sPathToImage += "/Walls/";     }
            else if (iTabState == (uint)TabState.Others)    { sPathToImage += "/Others/";    }
            else if (iTabState == (uint)TabState.Events)    { sPathToImage += "/Events/";    }
            else                                            { return null;                   }
            ////////////////////////////////////////////////////
            string sImageName = GetNameforCurrentTexture(); if (sImageName == null) { return null; }
            sPathToImage += sImageName + ".png";
            ////////////////////////////////////////////////////


            // Return The Texture If we already have it
            foreach (TexturesInfo TextureInfo in lTexturesList)
            {
                if (sPathToImage == TextureInfo.PathToTexture)
                {
                    return TextureInfo.Texture;
                }
            }


            ////////////////////////////////////////////////////
            // Otherwise Add it to the List
            if (!System.IO.File.Exists(sPathToImage)) { MessageBox.Show("Image File \n'" + sPathToImage + "'\nCannot be found"); return null; }
            Image TextureFromFile = Image.FromFile(sPathToImage);

            TexturesInfo TextInfo;
            TextInfo.TextureName = sImageName;
            TextInfo.PathToTexture = sPathToImage;
            TextInfo.Texture = TextureFromFile;
            lTexturesList.Add(TextInfo);
            ////////////////////////////////////////////////////
            return TextureFromFile;
        }





        //=====================================
        //     Get Images for Current State
        //=====================================
        private string GetNameforCurrentTexture()
        {
            if (iTabState == (uint)TabState.Platforms)
            {
                if      (iDataState == (uint)DataState.Platform1A)          { return "Platform1A";  }
                else if (iDataState == (uint)DataState.Platform1B)          { return "Platform1B";  }
                else if (iDataState == (uint)DataState.Platform1C)          { return "Platform1C";  }
                else if (iDataState == (uint)DataState.Platform1H)          { return "Platform1H";  }
                else if (iDataState == (uint)DataState.Platform1J)          { return "Platform1J";  }
                else if (iDataState == (uint)DataState.Platform1K)          { return "Platform1K";  }
                else if (iDataState == (uint)DataState.Platform1L)          { return "Platform1L";  }
                else if (iDataState == (uint)DataState.Platform1M)          { return "Platform1M";  }
                else if (iDataState == (uint)DataState.Log)                 { return "Log";         }
                else if (iDataState == (uint)DataState.Log1A)               { return "Log1A";       }
                else if (iDataState == (uint)DataState.Log1B)               { return "Log1B";       }
                else if (iDataState == (uint)DataState.Log1C)               { return "Log1C";       }
                else if (iDataState == (uint)DataState.Log2A)               { return "Log2A";       }
                else if (iDataState == (uint)DataState.Log2B)               { return "Log2B";       }
                else if (iDataState == (uint)DataState.Log2C)               { return "Log2C";       }
                else if (iDataState == (uint)DataState.Special1A)           { return "Special1A";   }
                else if (iDataState == (uint)DataState.Special1B)           { return "Special1B";   }
                else if (iDataState == (uint)DataState.Special1C)           { return "Special1C";   }
                else if (iDataState == (uint)DataState.Special1D)           { return "Special1D";   }
                else if (iDataState == (uint)DataState.Platform2A)          { return "Platform2A";  }
                else if (iDataState == (uint)DataState.Platform2B)          { return "Platform2B";  }
                else if (iDataState == (uint)DataState.Platform2C)          { return "Platform2C";  }
                else if (iDataState == (uint)DataState.Platform2D)          { return "Platform2D";  }
                else if (iDataState == (uint)DataState.Platform2E)          { return "Platform2E";  }
                else if (iDataState == (uint)DataState.Platform2F)          { return "Platform2F";  }
                else if (iDataState == (uint)DataState.Platform2G)          { return "Platform2G";  }
                else if (iDataState == (uint)DataState.Platform3A)          { return "Platform3A";  }
                else if (iDataState == (uint)DataState.Platform3B)          { return "Platform3B";  }
                else if (iDataState == (uint)DataState.Platform3C)          { return "Platform3C";  }
                else if (iDataState == (uint)DataState.Platform3D)          { return "Platform3D";  }
                else if (iDataState == (uint)DataState.Platform3E)          { return "Platform3E";  }
                else if (iDataState == (uint)DataState.Platform3F)          { return "Platform3F";  }
                else if (iDataState == (uint)DataState.Platform3G)          { return "Platform3G";  }
                else if (iDataState == (uint)DataState.Platform3H)          { return "Platform3H";  }
                else if (iDataState == (uint)DataState.Platform3I)          { return "Platform3I";  }
                else if (iDataState == (uint)DataState.Platform3J)          { return "Platform3J";  }
                else if (iDataState == (uint)DataState.Platform3K)          { return "Platform3K";  }
                else if (iDataState == (uint)DataState.Platform3L)          { return "Platform3L";  }
                else if (iDataState == (uint)DataState.Platform4A)          { return "Platform4A";  }
                else if (iDataState == (uint)DataState.Platform4B)          { return "Platform4B";  }
                else if (iDataState == (uint)DataState.Platform4C)          { return "Platform4C";  }
                else if (iDataState == (uint)DataState.Platform5A)          { return "Platform5A";  }
                else if (iDataState == (uint)DataState.Platform5B)          { return "Platform5B";  }
                else if (iDataState == (uint)DataState.Platform5C)          { return "Platform5C";  }
                else if (iDataState == (uint)DataState.Platform5D)          { return "Platform5D";  }
                else if (iDataState == (uint)DataState.Platform5E)          { return "Platform5E";  }
                else if (iDataState == (uint)DataState.Platform6A)          { return "Platform6A";  }
                else if (iDataState == (uint)DataState.Platform6B)          { return "Platform6B";  }
                else if (iDataState == (uint)DataState.Platform7A)          { return "Platform7A";  }
                else if (iDataState == (uint)DataState.Platform7B)          { return "Platform7B";  }
                else if (iDataState == (uint)DataState.Platform7C)          { return "Platform7C";  }
                else if (iDataState == (uint)DataState.Rock)                { return "Rock";        }
                else if (iDataState == (uint)DataState.Platform8A)          { return "Platform8A";  }
                else if (iDataState == (uint)DataState.Platform8B)          { return "Platform8B";  }
                else if (iDataState == (uint)DataState.Platform8C)          { return "Platform8C";  }
            }
            else if (iTabState == (uint)TabState.Walls)
            {
                if      (iDataState == (uint)DataState.Platform1WallA)      { return "Platform1WallA"; }
                else if (iDataState == (uint)DataState.Platform1WallB)      { return "Platform1WallB"; }
                else if (iDataState == (uint)DataState.Platform1WallC)      { return "Platform1WallC"; }
                else if (iDataState == (uint)DataState.Platform1WallD)      { return "Platform1WallD"; }
                else if (iDataState == (uint)DataState.Wood1A)              { return "Wood1A";      }
                else if (iDataState == (uint)DataState.Wood1B)              { return "Wood1B";      }
                else if (iDataState == (uint)DataState.Wood1C)              { return "Wood1C";      }
                else if (iDataState == (uint)DataState.Wood2A)              { return "Wood2A";      }
                else if (iDataState == (uint)DataState.Wood2B)              { return "Wood2B";      }
                else if (iDataState == (uint)DataState.Wood2C)              { return "Wood2C";      }
                else if (iDataState == (uint)DataState.Wood3A)              { return "Wood3A";      }
                else if (iDataState == (uint)DataState.Wood3B)              { return "Wood3B";      }
                else if (iDataState == (uint)DataState.Wood3C)              { return "Wood3C";      }
                else if (iDataState == (uint)DataState.Wood3D)              { return "Wood3D";      }
                else if (iDataState == (uint)DataState.Wood4A)              { return "Wood4A";      }
                else if (iDataState == (uint)DataState.Wood4B)              { return "Wood4B";      }
                else if (iDataState == (uint)DataState.Wood4C)              { return "Wood4C";      }
                else if (iDataState == (uint)DataState.Wood4D)              { return "Wood4D";      }
                else if (iDataState == (uint)DataState.Wood4E)              { return "Wood4E";      }
                else if (iDataState == (uint)DataState.Wood4F)              { return "Wood4F";      }
                else if (iDataState == (uint)DataState.Wall2P)              { return "Wall2P";      }
                else if (iDataState == (uint)DataState.Wall2Q)              { return "Wall2Q";      }
                else if (iDataState == (uint)DataState.Wall2R)              { return "Wall2R";      }
                else if (iDataState == (uint)DataState.Wall2S)              { return "Wall2S";      }
                else if (iDataState == (uint)DataState.Wall2T)              { return "Wall2T";      }
                else if (iDataState == (uint)DataState.Wall2K)              { return "Wall2K";      }
                else if (iDataState == (uint)DataState.Wall2L)              { return "Wall2L";      }
                else if (iDataState == (uint)DataState.Wall2M)              { return "Wall2M";      }
                else if (iDataState == (uint)DataState.Wall2N)              { return "Wall2N";      }
                else if (iDataState == (uint)DataState.Wall2O)              { return "Wall2O";      }
                else if (iDataState == (uint)DataState.Wall2F)              { return "Wall2F";      }
                else if (iDataState == (uint)DataState.Wall2G)              { return "Wall2G";      }
                else if (iDataState == (uint)DataState.Wall2H)              { return "Wall2H";      }
                else if (iDataState == (uint)DataState.Wall2I)              { return "Wall2I";      }
                else if (iDataState == (uint)DataState.Wall2J)              { return "Wall2J";      }
                else if (iDataState == (uint)DataState.Wall2B)              { return "Wall2B";      }
                else if (iDataState == (uint)DataState.Wall2C)              { return "Wall2C";      }
                else if (iDataState == (uint)DataState.Wall2D)              { return "Wall2D";      }
                else if (iDataState == (uint)DataState.Wall2E)              { return "Wall2E";      }
                else if (iDataState == (uint)DataState.Wall2A)              { return "Wall2A";      }
                else if (iDataState == (uint)DataState.Wall1F)              { return "Wall1F";      }
                else if (iDataState == (uint)DataState.Wall1G)              { return "Wall1G";      }
                else if (iDataState == (uint)DataState.Wall1L)              { return "Wall1L";      }
                else if (iDataState == (uint)DataState.Wall1C)              { return "Wall1C";      }
                else if (iDataState == (uint)DataState.Wall1B)              { return "Wall1B";      }
                else if (iDataState == (uint)DataState.Wall1D)              { return "Wall1D";      }
                else if (iDataState == (uint)DataState.Wall1I)              { return "Wall1I";      }
                else if (iDataState == (uint)DataState.Wall1H)              { return "Wall1H";      }
                else if (iDataState == (uint)DataState.Wall1K)              { return "Wall1K";      }
                else if (iDataState == (uint)DataState.Wall1J)              { return "Wall1J";      }
                else if (iDataState == (uint)DataState.Wall1O)              { return "Wall1O";      }
                else if (iDataState == (uint)DataState.Wall1N)              { return "Wall1N";      }
                else if (iDataState == (uint)DataState.Wall1M)              { return "Wall1M";      }
                else if (iDataState == (uint)DataState.Wall1P)              { return "Wall1P";      }
                else if (iDataState == (uint)DataState.Wall1Q)              { return "Wall1Q";      }
                else if (iDataState == (uint)DataState.Wall1E)              { return "Wall1E";      }
                else if (iDataState == (uint)DataState.Wall1A)              { return "Wall1A";      }
                else if (iDataState == (uint)DataState.Wall2EdgeL)          { return "Wall2EdgeL";  }
                else if (iDataState == (uint)DataState.Wall2EdgeK)          { return "Wall2EdgeK";  }
                else if (iDataState == (uint)DataState.Wall2EdgeF)          { return "Wall2EdgeF";  }
                else if (iDataState == (uint)DataState.Wall2EdgeG)          { return "Wall2EdgeG";  }
                else if (iDataState == (uint)DataState.Wall2EdgeH)          { return "Wall2EdgeH";  }
                else if (iDataState == (uint)DataState.Wall2EdgeI)          { return "Wall2EdgeI";  }
                else if (iDataState == (uint)DataState.Wall2EdgeJ)          { return "Wall2EdgeJ";  }
                else if (iDataState == (uint)DataState.Wall2EdgeB)          { return "Wall2EdgeB";  }
                else if (iDataState == (uint)DataState.Wall2EdgeC)          { return "Wall2EdgeC";  }
                else if (iDataState == (uint)DataState.Wall2EdgeD)          { return "Wall2EdgeD";  }
                else if (iDataState == (uint)DataState.Wall2EdgeE)          { return "Wall2EdgeE";  }
                else if (iDataState == (uint)DataState.Wall2EdgeA)          { return "Wall2EdgeA";  }
                else if (iDataState == (uint)DataState.Wall2X)              { return "Wall2X";      }
                else if (iDataState == (uint)DataState.Wall2U)              { return "Wall2U";      }
                else if (iDataState == (uint)DataState.Wall2V)              { return "Wall2V";      }
                else if (iDataState == (uint)DataState.Wall2W)              { return "Wall2W";      }
                else if (iDataState == (uint)DataState.Platform5WallD)      { return "Platform5WallD"; }
                else if (iDataState == (uint)DataState.Platform5WallC)      { return "Platform5WallC"; }
                else if (iDataState == (uint)DataState.Platform5WallB)      { return "Platform5WallB"; }
                else if (iDataState == (uint)DataState.Platform5WallA)      { return "Platform5WallA"; }
                else if (iDataState == (uint)DataState.Platform4WallA)      { return "Platform4WallA"; }
                else if (iDataState == (uint)DataState.Platform4WallB)      { return "Platform4WallB"; }
                else if (iDataState == (uint)DataState.Platform4WallC)      { return "Platform4WallC"; }
            }                                                                                       
            else if (iTabState == (uint)TabState.Others)                                            
            {                                                                                       
                if      (iDataState == (uint)DataState.Flower)              { return "Flower";      }
                else if (iDataState == (uint)DataState.Special1E)           { return "Special1E";   }
                else if (iDataState == (uint)DataState.Special1F)           { return "Special1F";   }
                else if (iDataState == (uint)DataState.Special1G)           { return "Special1G";   }
                else if (iDataState == (uint)DataState.Special1H)           { return "Special1H";   }
                else if (iDataState == (uint)DataState.Special1I)           { return "Special1I";   }
                else if (iDataState == (uint)DataState.Special1J)           { return "Special1J";   }
                else if (iDataState == (uint)DataState.Special1K)           { return "Special1K";   }
                else if (iDataState == (uint)DataState.Special1L)           { return "Special1L";   }
                else if (iDataState == (uint)DataState.Special1M)           { return "Special1M";   }
                else if (iDataState == (uint)DataState.Special1N)           { return "Special1N";   }
                else if (iDataState == (uint)DataState.Statue1A)            { return "Statue1A";    }
                else if (iDataState == (uint)DataState.Statue1B)            { return "Statue1B";    }
                else if (iDataState == (uint)DataState.Statue1C)            { return "Statue1C";    }
                else if (iDataState == (uint)DataState.Statue1D)            { return "Statue1D";    }
                else if (iDataState == (uint)DataState.Statue1E)            { return "Statue1E";    }
                else if (iDataState == (uint)DataState.Statue1F)            { return "Statue1F";    }
                else if (iDataState == (uint)DataState.Statue2A)            { return "Statue2A";    }
                else if (iDataState == (uint)DataState.Statue2B)            { return "Statue2B";    }
                else if (iDataState == (uint)DataState.Statue2C)            { return "Statue2C";    }
                else if (iDataState == (uint)DataState.Statue2D)            { return "Statue2D";    }
                else if (iDataState == (uint)DataState.Vines1A)             { return "Vines1A";     }
                else if (iDataState == (uint)DataState.Vines1B)             { return "Vines1B";     }
                else if (iDataState == (uint)DataState.Vines1C)             { return "Vines1C";     }
                else if (iDataState == (uint)DataState.Vines2A)             { return "Vines2A";     }
                else if (iDataState == (uint)DataState.Vines2B)             { return "Vines2B";     }
                else if (iDataState == (uint)DataState.Vines2C)             { return "Vines2C";     }
                else if (iDataState == (uint)DataState.Snowman1A)           { return "Snowman1A";   }
                else if (iDataState == (uint)DataState.Snowman1B)           { return "Snowman1B";   }
                else if (iDataState == (uint)DataState.Snowman1C)           { return "Snowman1C";   }
                else if (iDataState == (uint)DataState.Snowman1D)           { return "Snowman1D";   }
                else if (iDataState == (uint)DataState.Shading4P)           { return "Shading4P";   }
                else if (iDataState == (uint)DataState.Shading4K)           { return "Shading4K";   }
                else if (iDataState == (uint)DataState.Shading4L)           { return "Shading4L";   }
                else if (iDataState == (uint)DataState.Shading4M)           { return "Shading4M";   }
                else if (iDataState == (uint)DataState.Shading4N)           { return "Shading4N";   }
                else if (iDataState == (uint)DataState.Shading4O)           { return "Shading4O";   }
                else if (iDataState == (uint)DataState.Shading4F)           { return "Shading4F";   }
                else if (iDataState == (uint)DataState.Shading4G)           { return "Shading4G";   }
                else if (iDataState == (uint)DataState.Shading4H)           { return "Shading4H";   }
                else if (iDataState == (uint)DataState.Shading4I)           { return "Shading4I";   }
                else if (iDataState == (uint)DataState.Shading4J)           { return "Shading4J";   }
                else if (iDataState == (uint)DataState.Shading4E)           { return "Shading4E";   }
                else if (iDataState == (uint)DataState.Shading4C)           { return "Shading4C";   }
                else if (iDataState == (uint)DataState.Shading4B)           { return "Shading4B";   }
                else if (iDataState == (uint)DataState.Shading4A)           { return "Shading4A";   }
                else if (iDataState == (uint)DataState.Shading4D)           { return "Shading4D";   }
                else if (iDataState == (uint)DataState.Shading3B)           { return "Shading3B";   }
                else if (iDataState == (uint)DataState.Shading3C)           { return "Shading3C";   }
                else if (iDataState == (uint)DataState.Shading3D)           { return "Shading3D";   }
                else if (iDataState == (uint)DataState.Shading3E)           { return "Shading3E";   }
                else if (iDataState == (uint)DataState.Shading3F)           { return "Shading3F";   }
                else if (iDataState == (uint)DataState.Shading3G)           { return "Shading3G";   }
                else if (iDataState == (uint)DataState.Shading3H)           { return "Shading3H";   }
                else if (iDataState == (uint)DataState.Shading3I)           { return "Shading3I";   }
                else if (iDataState == (uint)DataState.Shading3J)           { return "Shading3J";   }
                else if (iDataState == (uint)DataState.Shading3K)           { return "Shading3K";   }
                else if (iDataState == (uint)DataState.Shading3A)           { return "Shading3A";   }
                else if (iDataState == (uint)DataState.Shading2F)           { return "Shading2F";   }
                else if (iDataState == (uint)DataState.Shading2K)           { return "Shading2K";   }
                else if (iDataState == (uint)DataState.Shading2M)           { return "Shading2M";   }
                else if (iDataState == (uint)DataState.Shading2H)           { return "Shading2H";   }
                else if (iDataState == (uint)DataState.Shading2C)           { return "Shading2C";   }
                else if (iDataState == (uint)DataState.Shading2E)           { return "Shading2E";   }
                else if (iDataState == (uint)DataState.Shading2J)           { return "Shading2J";   }
                else if (iDataState == (uint)DataState.Shading2I)           { return "Shading2I";   }
                else if (iDataState == (uint)DataState.Shading2D)           { return "Shading2D";   }
                else if (iDataState == (uint)DataState.Shading2G)           { return "Shading2G";   }
                else if (iDataState == (uint)DataState.Shading2L)           { return "Shading2L";   }
                else if (iDataState == (uint)DataState.Shading2B)           { return "Shading2B";   }
                else if (iDataState == (uint)DataState.Shading2A)           { return "Shading2A";   }
                else if (iDataState == (uint)DataState.Shading1N)           { return "Shading1N";   }
                else if (iDataState == (uint)DataState.Shading1M)           { return "Shading1M";   }
                else if (iDataState == (uint)DataState.Shading1E)           { return "Shading1E";   }
                else if (iDataState == (uint)DataState.Shading1K)           { return "Shading1K";   }
                else if (iDataState == (uint)DataState.Shading1B)           { return "Shading1B";   }
                else if (iDataState == (uint)DataState.Shading1C)           { return "Shading1C";   }
                else if (iDataState == (uint)DataState.Shading1D)           { return "Shading1D";   }
                else if (iDataState == (uint)DataState.Shading1G)           { return "Shading1G";   }
                else if (iDataState == (uint)DataState.Shading1F)           { return "Shading1F";   }
                else if (iDataState == (uint)DataState.Shading1H)           { return "Shading1H";   }
                else if (iDataState == (uint)DataState.Shading1I)           { return "Shading1I";   }
                else if (iDataState == (uint)DataState.Shading1J)           { return "Shading1J";   }
                else if (iDataState == (uint)DataState.Shading1L)           { return "Shading1L";   }
                else if (iDataState == (uint)DataState.Shading1A)           { return "Shading1A";   }
            }
            else if (iTabState == (uint)TabState.Events)
            {
                if      (iDataState == (uint)DataState.PlayerStart)         { return "Player_Start";    }
                else if (iDataState == (uint)DataState.Checkpoint1A)        { return "Checkpoint1A";    }
                else if (iDataState == (uint)DataState.Star_LevelFinisher)  { return "Star_LevelFinisher"; }
                else if (iDataState == (uint)DataState.Enemy_Bunny)         { return "Enemy_Bunny";     }
                else if (iDataState == (uint)DataState.Enemy_Snake)         { return "Enemy_Snake";     }
                else if (iDataState == (uint)DataState.Enemy_BlueSlime)     { return "Enemy_BlueSlime"; }
                else if (iDataState == (uint)DataState.Enemy_GreenSlime)    { return "Enemy_GreenSlime"; }
                else if (iDataState == (uint)DataState.Enemy_Imp)           { return "Enemy_Imp";       }
                else if (iDataState == (uint)DataState.Enemy_Succubus)      { return "Enemy_Succubus";  }
                else if (iDataState == (uint)DataState.Green_Crystal)       { return "Green_Crystal";   }
                else if (iDataState == (uint)DataState.Blue_Crystal)        { return "Blue_Crystal";    }
                else if (iDataState == (uint)DataState.Red_Crystal)         { return "Red_Crystal";     }
                else if (iDataState == (uint)DataState.Purple_Crystal)      { return "Purple_Crystal";  }
            }
            /* Otherwise */ return null;
        }
    }
}
