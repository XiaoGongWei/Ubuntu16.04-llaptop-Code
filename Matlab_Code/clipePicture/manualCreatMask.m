function manualCreatMask( image_data,  image_file_name, isdelete)
isdelete = 0;
if nargin > 2
    isdelete = 1;
end
[image_floder, file_name] = fileparts(image_file_name); % get file path and name
% split_char = filesep;
h_image_data = figure('Name', image_file_name, 'position', [0, 0, 500, 500]);
hold on
set(h_image_data, 'color', [0, 1, 1]);
imshow(image_data, 'InitialMagnification', 'fit');
all_position = [];
[image_rows, image_cols, image_chanle] = size(image_data);
all_maskImage = double(zeros(image_rows, image_cols));
% use get mulitply Poly
while 1
    isWant = qusestionDlg('Do you want get Water Area');
    if isWant == 0
        break;
    end
    h_Poly = impoly(gca);
    if isempty(h_Poly) || ~ishandle(h_image_data)
        return;
    end
    new_mask = h_Poly.createMask();
    all_maskImage = all_maskImage + double(new_mask);
    position = getPosition(h_Poly);
    all_position = [all_position;position];
end
maskImage = logical(all_maskImage);
save_mask_name = [file_name '_mask.tif'];
path_name = fullfile(image_floder, save_mask_name);
isFineshed = 1;
% isFineshed = qusestionDlg('Do you get Water Area');
if isFineshed == 1 && size(all_position, 1) > 2 
    h_contrast = figure('Name', 'contrast');
    subplot(1,2,1)
    imshow(image_data, 'InitialMagnification', 'fit');
    subplot(1,2,2)
%     maskedImage = image_data(:,:,1) .* cast(~maskImage, 'like', image_data);
    imshow(maskImage, 'InitialMagnification', 'fit');
    isRight = qusestionDlg('Dou you wang save maskImage');
    if isRight == 1
        imwrite(maskImage, path_name);
    end
    if ishandle(h_contrast)
        close(h_contrast);
    end
else
    imwrite(maskImage, path_name);
    if exist(image_file_name, 'file') && isdelete
        delete(image_file_name);
    end
end

if ishandle(h_image_data)
    close(h_image_data);
end

end

function isFineshed = qusestionDlg(infor_str)
if nargin < 1
   infor_str = 'Warning';
end
isFineshed = 0;
choice = questdlg(infor_str, 'Warning', 'Yes', 'No', 'No');
switch choice
    case 'Yes'
        isFineshed = 1;
    case 'No'
        isFineshed = 0;
end
end
