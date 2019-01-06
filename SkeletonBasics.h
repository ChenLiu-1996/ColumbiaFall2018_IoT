//------------------------------------------------------------------------------
// <copyright file="SkeletonBasics.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

/*
This file is modified to accomodate the SkeletonBasics_color.cpp.
*/

#pragma once

#include "resource.h"
#include "NuiApi.h"
#include <string>
#include "dwrite.h"
#include "ImageRenderer.h"

class CSkeletonBasics
{
	static const int        cColorWidth = 640;
	static const int        cColorHeight = 480;

    static const int        cScreenWidth  = 320;
    static const int        cScreenHeight = 240;

    static const int        cStatusMessageMaxLen = MAX_PATH*2;

public:
    /// <summary>
    /// Constructor
    /// </summary>
    CSkeletonBasics();

    /// <summary>
    /// Destructor
    /// </summary>
    ~CSkeletonBasics();

    /// <summary>
    /// Handles window messages, passes most to the class instance to handle
    /// </summary>
    /// <param name="hWnd">window message is for</param>
    /// <param name="uMsg">message</param>
    /// <param name="wParam">message data</param>
    /// <param name="lParam">additional message data</param>
    /// <returns>result of message processing</returns>
    static LRESULT CALLBACK MessageRouter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    /// <summary>
    /// Handle windows messages for a class instance
    /// </summary>
    /// <param name="hWnd">window message is for</param>
    /// <param name="uMsg">message</param>
    /// <param name="wParam">message data</param>
    /// <param name="lParam">additional message data</param>
    /// <returns>result of message processing</returns>
    LRESULT CALLBACK        DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    /// <summary>
    /// Creates the main window and begins processing
    /// </summary>
    /// <param name="hInstance"></param>
    /// <param name="nCmdShow"></param>
    int                     Run(HINSTANCE hInstance, int nCmdShow);

private:
    HWND                    m_hWnd;

    bool                    m_bSeatedMode;

    // Current Kinect
    INuiSensor*             m_pNuiSensor;

    // Skeletal drawing
    ID2D1HwndRenderTarget*   m_pRenderTarget;
    ID2D1SolidColorBrush*    m_pBrushJointTracked;
    ID2D1SolidColorBrush*    m_pBrushJointInferred;
    ID2D1SolidColorBrush*    m_pBrushBoneTracked;
    ID2D1SolidColorBrush*    m_pBrushBoneInferred;
    D2D1_POINT_2F            m_Points[NUI_SKELETON_POSITION_COUNT];

    // Direct2D
    ID2D1Factory*           m_pD2DFactory;
	  ImageRenderer*          m_pDrawColor; // Color stream

    HANDLE                  m_pSkeletonStreamHandle;
   	HANDLE                  m_hNextSkeletonEvent;
	  HANDLE                  m_pColorStreamHandle; // Color stream
  	HANDLE                  m_hNextColorFrameEvent; // Color stream

  	// DirectWrite
  	IDWriteFactory*			m_pDWriteFactory; // Text
  	IDWriteTextFormat*		m_pTextFormat; // Text

    /// <summary>
    /// Main processing function
    /// </summary>
    void                    Update();

    /// <summary>
    /// Create the first connected Kinect found
    /// </summary>
    /// <returns>S_OK on success, otherwise failure code</returns>
    HRESULT                 CreateFirstConnected();

    /// <summary>
    /// Handle new skeleton data
    /// </summary>
    void                    ProcessSkeleton();

    /// <summary>
    /// Ensure necessary Direct2d resources are created
    /// </summary>
    /// <returns>S_OK if successful, otherwise an error code</returns>
    HRESULT                 EnsureDirect2DResources( );

    /// <summary>
    /// Dispose Direct2d resources
    /// </summary>
    void                    DiscardDirect2DResources( );

	  /// <summary>
	  /// Calculates the angle formed by three joints "Angle(ABC)"
	  /// </summary>
	  /// <param name="jointA_x">x coordinate of joint A</param>
	  /// <param name="jointA_y">y coordinate of joint A</param>
	  /// <param name="jointB_x">x coordinate of joint B (the tip of the angle)</param>
	  /// <param name="jointB_y">y coordinate of joint B (the tip of the angle)</param>
	  /// <param name="jointC_x">x coordinate of joint C</param>
	  /// <param name="jointC_y">y coordinate of joint C</param>
	  float					FindAngle(float jointA_x, float jointA_y, float jointB_x, float jointB_y, float jointC_x, float jointC_y);

	  /// <summary>
	  /// Draws the angle at the given joint
	  /// </summary>
	  /// <param name="joint_coordinates">[D2D1_POINT_2F]coordinates of the joint</param>
	  /// <param name="angle">[float]angle of the joint</param>
	  void CSkeletonBasics::DrawAngleOnJoint(D2D1_POINT_2F joint_coordinates, float angle);

	  /// <summary>
    /// Draws a bone line between two joints
    /// </summary>
    /// <param name="skel">skeleton to draw bones from</param>
    /// <param name="joint0">joint to start drawing from</param>
    /// <param name="joint1">joint to end drawing at</param>
    void                    DrawBone(const NUI_SKELETON_DATA & skel, NUI_SKELETON_POSITION_INDEX bone0, NUI_SKELETON_POSITION_INDEX bone1);

    /// <summary>
    /// Draws a skeleton
    /// </summary>
    /// <param name="skel">skeleton to draw</param>
    /// <param name="windowWidth">width (in pixels) of output buffer</param>
    /// <param name="windowHeight">height (in pixels) of output buffer</param>
    void                    DrawSkeleton(const NUI_SKELETON_DATA & skel, int windowWidth, int windowHeight);

    /// <summary>
    /// Converts a skeleton point to screen space
    /// </summary>
    /// <param name="skeletonPoint">skeleton point to tranform</param>
    /// <param name="width">width (in pixels) of output buffer</param>
    /// <param name="height">height (in pixels) of output buffer</param>
    /// <returns>point in screen-space</returns>
    D2D1_POINT_2F           SkeletonToScreen(Vector4 skeletonPoint, int width, int height);


    /// <summary>
    /// Set the status bar message
    /// </summary>
    /// <param name="szMessage">message to display</param>
    void                    SetStatusMessage(WCHAR* szMessage);
};
